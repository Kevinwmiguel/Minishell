/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:41:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/02 15:02:05 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	run_children(t_shell *shell, char **argv, t_pipexinfo *info)
{
	t_red	*redir;

	redir = shell->cmd->redirect;
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
	executor(shell, argv);
}

void	run_child(char **argv, t_shell *shell, t_pipexinfo *info)
{
	int	processor;

	processor = fork();
	if (processor == 0)
	{
		signal_search(CHILD);
		run_children(shell, argv, info);
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
