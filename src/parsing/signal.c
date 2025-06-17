/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:31 by jmehmy            #+#    #+#             */
/*   Updated: 2025/06/17 18:58:21 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal g_signal = {false, 0};

void	handle_sigint(int code, t_signal *signal)
{
	static t_signal	*global;

	if (!global)
	{
		global = signal;
		return ;
	}
	(void)code;
	if (global->heredoc)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (global->pid == 0)
		rl_redisplay();
}

void	handle_sigsegv(int code)
{
	(void)code;
	write(1, "Segmentation fault\n", 19);
}

void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
}
