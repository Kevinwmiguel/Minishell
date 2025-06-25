/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:02 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/26 00:42:19 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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
	if (redir && redir->heredoc > 0)
		dup2(redir->heredoc, STDIN_FILENO);
	else if (redir && redir->infd > 0)
		dup2(redir->infd, STDIN_FILENO);
	else if (info->fd_in > 0 && info->fd_in != STDIN_FILENO)
		dup2(info->fd_in, STDIN_FILENO);
	if (redir && redir->outfd > 0)
		dup2(redir->outfd, STDOUT_FILENO);
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
		final_cleaner(shell);
	}
	else if (processor > 0)
		waitpid(processor, NULL, 0);
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

	ft_bzero(&info, sizeof(t_pipexinfo));
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
