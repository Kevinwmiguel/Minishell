/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:42:18 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 19:00:54 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit(130);
	}
}

static void	set_signal_root(struct sigaction *sa)
{
	sa->sa_sigaction = root_signal;
	sa->sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return ;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	set_signal_child(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sa->sa_flags = 0;
	if (sigemptyset(&sa->sa_mask) != 0)
		return ;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

static void set_signal_heredoc(struct sigaction *sa)
{
		sa->sa_handler = signal_heredoc;
		sa->sa_flags = 0;
		//sigemptyset(&sa.sa_mask);
		if (sigemptyset(&sa->sa_mask) != 0)
			return ;
		sigaction(SIGINT, sa, NULL);
		signal(SIGQUIT, SIG_IGN);
}

void	signal_search(t_sig_t t)
{
	static struct sigaction	sa;

	if (t == ROOT)
		set_signal_root(&sa);
	else if (t == CHILD)
		set_signal_child(&sa);
	else if (t == HEREDOC_CHILD)
		set_signal_heredoc(&sa);
	else if (t == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
