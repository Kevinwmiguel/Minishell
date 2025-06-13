/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:39:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 22:31:18 by kwillian         ###   ########.fr       */
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

void	free_redirections(t_red *red)
{
	t_red	*tmp;

	while (red)
	{
		tmp = red->next;
		if (red->pipe)
			free(red->pipe);
		free(red);
		red = tmp;
	}
}

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
			return (exit_shell(shell), 0);
		add_history(input);
		ex(shell);
		execute_all_cmds(shell);
		free(input);
	}
	return (1);
}

void init(t_shell *shell, char **env)
{
	shell->env = dptr_dup(env);
	shell->exp = dptr_dup(env);
	if (!shell->env)
	{
		// Trate erro, se quiser
		// Por exemplo: print e exit
		perror("Failed to duplicate env");
		exit(EXIT_FAILURE);
	}
	shell->count = 1;
}

void	print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	printf("======================\n");
	int i = 0;
	while (cmd->args[i])
		printf("%s\n", cmd->args[i++]);
	printf("redirect: %i\n", cmd->redirect != NULL);
	print_cmd(cmd->next);
}

void ex(t_shell *shell)
{
	t_cmd *begin = ft_calloc(1, sizeof(t_cmd));
	t_cmd *next = ft_calloc(1, sizeof(t_cmd));

	begin->args = ft_calloc(3, sizeof(char *));
	next->args = ft_calloc(3, sizeof(char *));

	begin->args[0] = ft_strdup("ls");
	begin->args[1] = ft_strdup("-la"); // caso deseje adicionar
	next->args[0] = get_path("exit", shell->env);
	begin->next = next;
	shell->cmd = begin;

	print_cmd(begin);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	//int	i = 0;

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
	//checarSHLVL
	run(shell);
	return (0);
}
