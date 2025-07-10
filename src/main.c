/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:08:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/10 00:33:30 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	init(t_shell *shell, char **env)
{
	shell->env = NULL;
	shell->exp = NULL;
	shell->cmd = NULL;
	shell->cmd_ready = NULL;
	shell->exit_code = 0;
	shell->env = dptr_dup(env);
	shell->begin = NULL;
	if (!shell->env)
	{
		perror("Failed to duplicate env");
		exit(EXIT_FAILURE);
	}
	update_shlvl(shell);
	shell->exp = build_export(shell);
	shell->count = 0;
}

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
