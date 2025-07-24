/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:03:11 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 13:50:12 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	close_redirections(t_cmd *cmd)
{
	t_red	*redir;

	if (!cmd || !cmd->redirect)
		return ;
	redir = cmd->redirect;
	while (redir)
	{
		if (redir->infd > 2)
			close(redir->infd);
		if (redir->outfd > 2)
			close(redir->outfd);
		if (redir->heredoc > 2)
			close(redir->heredoc);
		redir = redir->next;
	}
}

void	get_out(t_shell *shell)
{
	final_cleaner(shell);
	close_extra_fds();
	exit(0);
}

void	heredoc_ctrl_c(t_shell *shell)
{
	if (g_heredoc_interrupted == 1)
	{
		close_extra_fds();
		freedom(shell);
		exit(130);
	}
	if (shell->mistake2 == 1)
	{
		close_extra_fds();
		freedom(shell);
		exit(0);
	}
}
