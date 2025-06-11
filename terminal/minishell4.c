/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:44:46 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 14:28:06 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

void	exec_builtin(int flag, char **command, char **env, t_shell *utils)
{
	int		y;

	utils->echo_breed = NULL;
	y = len_dp(command);
	utils->count_hp = where_is_echox(command);
	if (utils->count_hp != -1)
		utils->echo_breed = double_to_one(utils->command);
	if (utils->input)
		input_fixer(utils->input);
	if (flag == 1 && utils->count_hp != -1)
		build_echo(utils->echo_breed + 5, utils, 0, -1);
	else if (flag == 2)
		build_cd(y, command, env, utils);
	else if (flag == 3)
		build_pwd(y, command, utils);
	else if (flag == 4)
		utils->exp = build_export(y, command, utils);
	else if (flag == 5)
		utils->exp = build_unset(y, command, utils->exp, -1);
	else if (flag == 6)
		build_env(y, command, utils);
	else if (flag == 7)
		build_exit(command, utils);
	if (utils->echo_breed)
		free(utils->echo_breed);
}

void	index_reset(t_shell *utils)
{
	utils->j = 0;
	utils->export->i = 0;
	utils->export->j = 0;
	utils->export->k = 0;
	utils->export->l = 0;
	utils->export->m = 0;
	utils->export->n = 0;
	utils->export->x = 0;
	utils->export->flag = 0;
}

int	scary_thing(t_pipesort	*piped, t_shell *utils)
{
	int			i;
	t_pipesort	*piped_clone;
	t_pipesort	*piped_clone2;

	i = -1;
	piped_clone = piped;
	piped_clone2 = piped;
	while (utils->command[++i])
	{
		piped_clone->next = ft_calloc(1, sizeof(t_pipesort));
		piped_clone->content = ft_split(utils->command[i], ' ');
		piped_clone->id = i;
		piped_clone->redirection = redirection_verifier(piped_clone);
		if (piped_clone->redirection == true)
		{
			if (correct_redirection(piped_clone->content) == 0)
				return (printf("The redirection identation is incorrect\n"), 0);
		}
		piped_clone = piped_clone->next;
		piped_clone->prev = piped_clone2;
		piped_clone2 = piped_clone2->next;
	}
	free_dptr(piped_clone->content);
	return (1);
}
