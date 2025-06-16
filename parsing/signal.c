/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:31 by jmehmy            #+#    #+#             */
/*   Updated: 2025/06/16 14:07:06 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal g_signal = {false, 0};

void	handle_sigint(int code)
{
	(void)code;
	if (g_signal.heredoc)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal.pid == 0)
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
