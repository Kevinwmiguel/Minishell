/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:59:42 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 19:00:18 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	root_signal(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_heredoc_child(t_shell *shell, char *limiter, int *fd)
{
	signal_search(HEREDOC_CHILD);
	close(fd[0]);
	handle_heredoc_input(shell, limiter, fd[1]);
	close(fd[1]);
	exit(0);
}
