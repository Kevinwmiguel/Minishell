/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/24 17:57:54 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*checker_path(t_shell *shell, char **paths, char *tmp)
{
	char	*fullpath;
	int		i;

	i = 0;
	fullpath = NULL;
	if (shell->cmd->args[0][0] == '.' || shell->cmd->args[0][0] == '/')
	{
		if (access(shell->cmd->args[0], X_OK) == 0)
			return (ft_strdup(shell->cmd->args[0]));
		else
			return (NULL);
	}
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpath = ft_strjoin(tmp, shell->cmd->args[0]);
		free(tmp);
		if (access(fullpath, X_OK) == 0)
			break ;
		free(fullpath);
		fullpath = NULL;
		i++;
	}
	return (fullpath);
}

void	path_cleaner(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		if (i == 0)
			free(paths[i] - 5);
		else
			free(paths[i]);
		i++;
	}
	if (paths)
		free(paths);
}

char	**pick_path(char **envp)
{
	char	**path;
	int		index;

	index = 0;
	path = NULL;
	while (envp && envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			path = ft_split(envp[index], ':');
			if (!path)
				path_cleaner(path);
			else
				path[0] = path[0] + 5;
			break ;
		}
		index++;
	}
	return (path);
}

void	builtins_analyzer(t_shell *shell, int flag)
{
	(void)shell;
	if (flag == 1)
		build_echo(shell, shell->cmd->args);
	if (flag == 2)
		build_cd(shell);
	if (flag == 3)
		build_pwd(shell);
	if (flag == 4)
		build_export(shell);
	if (flag == 5)
		build_unset(shell);
	if (flag == 6)
		build_env(shell);
	if (flag == 7)
		build_exit(shell);
}

void	executor(t_shell *shell, char **argv)
{
	int		flag;
	char	*fullpath;

	if (!argv || !argv[0])
		exit(1);
	flag = builtins(shell->cmd->args[0]);
	if (flag > 0)
	{
		builtins_analyzer(shell, flag);
		exit(1);
	}
	else
	{
		fullpath = get_path(shell->cmd->args[0], shell->env);
		execve(fullpath, argv, shell->env);
		perror("execve: ");
		exit(1);
	}
}

void	run_child(t_shell *shell, char **argv, t_pipexinfo *info)
{
	t_red	*redir = shell->cmd->redirect;

	// printf("valores heredoc %d \n\n", redir->heredoc);
	// printf("valores fd[0] %d \n\n", info->fd[0]);
	// printf("valores fd[1] %d \n\n", info->fd[1]);
	// printf("valores fd_in %d\n\n", info->fd_in);
	// printf("valores outfd %d \n\n", redir->outfd);
	// exit(1);
	// ---------- STDIN ----------
	if (redir && redir->heredoc > 0)
		dup2(redir->heredoc, STDIN_FILENO);
	else if (redir && redir && redir->infd > 0)
		dup2(redir->infd, STDIN_FILENO);
	else if (info->fd_in > 0 && info->fd_in != STDIN_FILENO)
		dup2(info->fd_in, STDIN_FILENO);

	// ---------- STDOUT ----------
	if (redir && redir->outfd > 0)
		dup2(redir->outfd, STDOUT_FILENO);
	else if (info->fd[1] > 0)
		dup2(info->fd[1], STDOUT_FILENO);

	// ---------- FECHAMENTO DOS DESNECESSÁRIOS ----------
	if (info->fd[0] > 0)
		close(info->fd[0]);
	if (info->fd[1] > 0)
		close(info->fd[1]);
	if (info->fd_in > 0 && info->fd_in != STDIN_FILENO)
		close(info->fd_in);

	executor(shell, argv);
}

void	fork_comms(char **argv, t_shell *shell, t_pipexinfo *info)
{
	int	processor;

	processor = fork();
	if (processor == 0)
	{
		signal_search(CHILD);
		run_child(shell, argv, info);
	}
	else if (processor > 0)
	{
		// Aqui SIM devemos esperar o processo SE estamos executando isoladamente (caso count == 1)
		waitpid(processor, NULL, 0);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

static void	fork_loop(t_shell *shell, t_pipexinfo *info)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		shell->cmd = cmd;
		if (cmd->next && pipe(info->fd) == -1)
			exit(1);
		if (!cmd->next)
		{
			info->fd[0] = -1;
			info->fd[1] = -1;
		}
		info->pid = fork();
		if (info->pid == 0)
		{
			if (info->fd[1] != -1)
				close(info->fd[0]);
			run_child(shell, cmd->args, info);
		}
		if (info->fd[1] != -1)
			close(info->fd[1]);
		if (info->fd_in != STDIN_FILENO)
			close(info->fd_in);
		info->fd_in = info->fd[0];
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
}

void	execute_all_cmds(t_shell *shell)
{
	t_pipexinfo	info;
	t_cmd		*cmd;

	info.fd_in = STDIN_FILENO;
	shell->count = 0;
	cmd = shell->cmd;
	while (cmd)
	{
		shell->count++;
		if (cmd->redirect)
			fixing_cmd_red(cmd);
		cmd = cmd->next;
	}
	if (shell->count == 1)
		return (builtins_dealer(shell, &info));
	fork_loop(shell, &info);
}
