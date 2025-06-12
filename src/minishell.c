/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:39:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 15:18:02 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_shell(t_shell *shell)
{
	(void) shell;
	printf("exit_shell\n");
}

int	run(t_shell *shell)
{
	char *input;
	
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			return (exit_shell(shell), 0);
		add_history(input);
		if(ft_strlen(input) != 0 && parse(shell, input))
		{
			shell->cmd = init_cmd(shell, shell->begin);
			exec(shell);
			free_token_lst(shell);
		}
		free(input);
	}
	return (1);
}

static void	init(t_shell *shell, char **env)
{

	shell->env = dptr_dup(env);
}

void print_cmd(t_cmd *cmd)
{
	if (!cmd) return;
	printf("======================\n");
	int i = 0;
	while (cmd->args[i])
		printf("%s\n", cmd->args[i++]);
	printf("redirect: %i\n", cmd->redirect != NULL);
	print_cmd(cmd->next);
}


char *get_path(char *cmd)
{
	return (cmd);
}
void ex(t_shell	*shell){

	char **cmd1 = ft_calloc(sizeof(char *), 3);

	cmd1[0] = get_path(ft_strdup("ls"));
	cmd1[1] = ft_strdup("-la");

	char **cmd2 = ft_calloc(sizeof(char *), 3);

	*cmd2 =  get_path(ft_strdup("wc"));

	t_cmd *next = ft_calloc(sizeof(t_cmd), 1);
	next->args = cmd2;
	t_cmd *begin = ft_calloc(sizeof(t_cmd), 1);
	begin->args=cmd1;	
	begin->next=next;
	shell->cmd = begin;

	print_cmd(begin);
}

int	main(int argc, char **argv, char **env)
{
	static t_shell	shell;

	(void) argc;
	(void) argv;
	init(&shell, env);
	// ex(&shell);
	run(&shell);
	rl_clear_history();
	return (0);
}
