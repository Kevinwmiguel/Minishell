/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:08:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/14 01:24:02 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static int	alloc_env_array(char ***env, int count)
{
	*env = malloc(sizeof(char *) * (count + 1));
	if (!*env)
		return (0);
	return (1);
}

void	prepare_env(t_shell *shell)
{
	int		i;
	char	*home;

	if (!alloc_env_array(&shell->env, 7))
		return ;
	home = getenv("HOME");
	i = 0;
	shell->env[i++] = get_pwd_var();
	shell->env[i++] = ft_strdup("LS_COLORS=");
	shell->env[i++] = ft_strdup("LESSCLOSE=/usr/bin/lesspipe %s %s");
	shell->env[i++] = ft_strdup("LESSOPEN=| /usr/bin/lesspipe %s");
	shell->env[i++] = get_path_var(home);
	shell->env[i++] = ft_strdup("_=/usr/bin/env");
	shell->env[i++] = ft_strdup("TERM=xterm-256color");
	shell->env[i] = NULL;
}

static int	has_minimum_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	init(t_shell *shell, char **env)
{
	shell->env = NULL;
	shell->exp = NULL;
	shell->cmd = NULL;
	shell->cmd_ready = NULL;
	shell->last_arg = NULL;
	shell->next_last_arg = NULL;
	shell->exit_code = 0;
	if (!has_minimum_env(env))
		prepare_env(shell);
	else
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
	// t_signal	signal;

	// signal = (t_signal){};
	// handle_sigint(0, &signal);
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
