/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:39:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/26 00:20:41 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

// void	free_redirections(t_red *red)
// {
// 	t_red	*tmp;

// 	while (red)
// 	{
// 		tmp = red->next;
// 		if (red->piped)
// 			free(red->piped);
// 		free(red);
// 		red = tmp;
// 	}
// }

int	run(t_shell *shell)
{
	char	*input;

	while (1)
	{
		signal_search(ROOT);
		input = readline("minishell: ");
		if (!input)
		{
			final_cleaner(shell);
			exit(1);
		}
		if (input[0] == '\0')
			continue ;
		add_history(input);
		if (ft_strlen(input) != 0 && process_shell_input(shell, input))
			shell->cmd = parse_cmd(shell, shell->begin);
		execute_all_cmds(shell);
		free_cmds(shell->cmd);
		free(input);
	}
	return (1);
}

static int	get_shlvl_index(t_shell *shell, int *current_lvl)
{
	int	i;

	i = 0;
	*current_lvl = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			*current_lvl = ft_atoi(shell->env[i] + 6);
			return (i);
		}
		i++;
	}
	return (-1);
}

void	update_shlvl(t_shell *shell)
{
	int		i;
	int		current_lvl;
	char	*lvl_str;
	char	*new_lvl;

	i = get_shlvl_index(shell, &current_lvl);
	current_lvl++;
	lvl_str = ft_itoa(current_lvl);
	new_lvl = ft_strjoin("SHLVL=", lvl_str);
	free(lvl_str);
	if (i >= 0)
	{
		free(shell->env[i]);
		shell->env[i] = new_lvl;
	}
	else
	{
		i = 0;
		while (shell->env[i])
			i++;
		shell->env = realloc(shell->env, sizeof(char *) * (i + 2));
		shell->env[i] = new_lvl;
		shell->env[i + 1] = NULL;
	}
}

void	init(t_shell *shell, char **env)
{
	shell->env = NULL;
	shell->exp = NULL;
	shell->env = dptr_dup(env);
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
