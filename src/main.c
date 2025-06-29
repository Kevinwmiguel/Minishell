/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:08:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/29 22:09:12 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	main(int argc, char **argv, char **env)
{
	t_shell		*shell;
	t_signal	signal;

	signal = (t_signal){};
	handle_sigint(0, &signal);
	(void) argc;
	(void) argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		perror("malloc failed");
		return (1);
	}
	init(shell, env);
	run(shell);
	return (0);
}
