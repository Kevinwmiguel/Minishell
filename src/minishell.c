/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:39:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/18 00:26:58 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void ex(t_shell	*shell);

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_split(cmd->args);
		if (cmd->redirect)
			free_redirections(cmd->redirect);
		free(cmd);
		cmd = tmp;
	}
}

void	final_cleaner(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmd)
		free_cmds(shell->cmd);
	if (shell->env)
		free_split(shell->env);
	if (shell->exp)
		free_split(shell->exp);
	free(shell);
}

void	exit_shell(t_shell *shell)
{
	(void) shell;
	printf("exit_shell\n");
}

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
		add_history(input);
		if (ft_strlen(input) != 0 && process_shell_input(shell, input))
		{
			shell->cmd = parse_cmd(shell, shell->begin);
		}
		execute_all_cmds(shell);
		free(input);
	}
	return (1);
}

void	update_shlvl(t_shell *shell)
{
	char	*lvl_str;
	char	*new_lvl;
	int		i;
	int		current_lvl;

	current_lvl = 0;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			current_lvl = ft_atoi(shell->env[i] + 6);
			break ;
		}
		i++;
	}
	current_lvl++;
	lvl_str = ft_itoa(current_lvl);
	new_lvl = ft_strjoin("SHLVL=", lvl_str);
	free(lvl_str);

	if (shell->env[i])
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

void init(t_shell *shell, char **env)
{
	shell->env = dptr_dup(env);
	shell->exp = dptr_dup(env);
	if (!shell->env)
	{
		perror("Failed to duplicate env");
		exit(EXIT_FAILURE);
	}
	update_shlvl(shell);
	shell->count = 0;
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	printf("======================\n");
	while (cmd->args[i])
		printf("%s\n", cmd->args[i++]);
	printf("redirect: %i\n", cmd->redirect != NULL);
	print_cmd(cmd->next);
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
		return 1;
	}
	shell->env = NULL;
	shell->exp = NULL;
	init(shell, env);
	run(shell);
	return (0);
}
