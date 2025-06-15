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

void	exit_shell(t_shell *shell)
{
	(void)shell;
	printf("exit_shell\n");
}

int	run(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			return (exit_shell(shell), 0);
		add_history(input);
		if (ft_strlen(input) != 0 && process_shell_input(shell, input))
		{
			shell->cmd = parse_cmd(shell, shell->begin);
			if (shell->cmd && is_builtin(shell->cmd->args[0]))
				exec_builtin(shell->cmd, shell);
			//print_cmd(shell->cmd);
		}
		free(input);
	}
	return (1);
}

static void	init(t_shell *shell, char **env)
{
	shell->env = dptr_dup(env);
}

char	*get_path(char *cmd)
{
	return (cmd);
}
void	ex(t_shell *shell)
{
	char	**cmd1;
	char	**cmd2;
	t_cmd	*next;
	t_cmd	*begin;

	cmd1 = ft_calloc(sizeof(char *), 3);
	cmd1[0] = get_path(ft_strdup("ls"));
	cmd1[1] = ft_strdup("-la");
	cmd2 = ft_calloc(sizeof(char *), 3);
	*cmd2 = get_path(ft_strdup("wc"));
	next = ft_calloc(sizeof(t_cmd), 1);
	next->args = cmd2;
	begin = ft_calloc(sizeof(t_cmd), 1);
	begin->args = cmd1;
	begin->next = next;
	shell->cmd = begin;
	print_cmd(begin);
}

int	main(int argc, char **argv, char **env)
{
	static t_shell	shell;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGABRT, &handle_sigabrt);

	init(&shell, env);
	// ex(&shell);
	run(&shell);
	rl_clear_history();
	return (0);
}
