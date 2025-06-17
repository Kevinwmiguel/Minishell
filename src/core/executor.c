/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/18 00:12:19 by kwillian         ###   ########.fr       */
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
		build_export(shell->exp);
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
	t_red	*redir;

	redir = shell->cmd->redirect;

	if (redir && redir->piped)
	{
		if (redir->piped->heredoc > 0)
			dup2(redir->piped->heredoc, STDIN_FILENO);
		else if (redir->piped->infd > 0)
			dup2(redir->piped->infd, STDIN_FILENO);
		else if (info->fd_in != STDIN_FILENO)
			dup2(info->fd_in, STDIN_FILENO);
	}
	else if (info->fd_in != STDIN_FILENO)
		dup2(info->fd_in, STDIN_FILENO);
	if (redir && redir->piped)
	{
		if (redir->piped->outfd > 0)
			dup2(redir->piped->outfd, STDOUT_FILENO);
		else if (info->fd[1] > 0)
			dup2(info->fd[1], STDOUT_FILENO);
	}
	else if (info->fd[1] > 0)
		dup2(info->fd[1], STDOUT_FILENO);
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
	else
	{
		waitpid(processor, NULL, 0);
		//build_exit(shell);
	}
}

