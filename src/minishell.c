/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:39:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/13 17:47:41 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	exec_clean(t_shell *shell, t_cmd *head)
{
	(void)head;
	shell->exit_code = 0;
	execute_all_cmds(shell);
	close_redirections(head);
	free_token_list(shell);
	free_cmds(head);
	shell->cmd = NULL;
}

int	run(t_shell *shell)
{
	char	*input;
	t_cmd	*head;

	head = NULL;
	while (1)
	{
		signal_search(ROOT);
		input = readline("minishell: ");
		if (!input)
			get_out(shell);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (ft_strlen(input) != 0 && process_shell_input(shell, input))
		{
			shell->cmd = parse_cmd(shell, shell->begin);
			head = shell->cmd;
			exec_clean(shell, head);
		}
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

void	update_shlvl_helper(t_shell *shell, int i, char *new_lvl)
{
	char	**tmp;

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
		tmp = realloc(shell->env, sizeof(char *) * (i + 2));
		if (!tmp)
		{
			free(new_lvl);
			return ;
		}
		shell->env = tmp;
		shell->env[i] = new_lvl;
		shell->env[i + 1] = NULL;
	}
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
	if (!lvl_str)
		return ;
	new_lvl = ft_strjoin("SHLVL=", lvl_str);
	free(lvl_str);
	if (!new_lvl)
		return ;
	update_shlvl_helper(shell, i, new_lvl);
}
