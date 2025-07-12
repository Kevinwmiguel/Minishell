/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:41:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/11 12:41:52 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static int	is_heredoc(t_cmd *cmd)
{
	t_red	*redir = cmd->redirect;

	while (redir)
	{
		if (redir->type == HEREDOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	run_children(t_shell *shell, t_cmd_r *clean, t_pipexinfo *info,
		t_cmd *cmd)
{
	t_red	*redir;

	redir = cmd->redirect;
	if (redir && redir->heredoc > 0)
		dup2(redir->heredoc, STDIN_FILENO);
	else if (redir && redir->infd > 0)
	{
		dup2(redir->infd, STDIN_FILENO);
		close(redir->infd);
	}
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
	executor(shell, clean);
}

void	run_child(t_cmd_r *clean, t_shell *shell, t_pipexinfo *info)
{
	int	processor;
	int	status;

	processor = fork();
	if (processor == 0)
	{
		if (is_heredoc(shell->cmd))
			signal_search(HEREDOC_CHILD);
		else
			signal_search(CHILD);
		run_children(shell, clean, info, shell->cmd);
	}
	else if (processor > 0)
	{
		waitpid(processor, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else
			shell->exit_code = 1;
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
