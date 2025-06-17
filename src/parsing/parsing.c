/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:08 by jmehmy            #+#    #+#             */
/*   Updated: 2025/06/16 15:19:21 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_shell *data, t_token *token)
{
	t_cmd	*cmd;

	(void)data;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = get_cmd(token);
	cmd->next = NULL;
	get_redirection(cmd, token);
	return (cmd);
}

int	process_shell_input(t_shell *data, char *str)
{
	char	*str_parse;

	if (ft_strlen(str) == 0)
		return (0);
	if (verify_closed_quote(str))
	{
		write(1, "Error: Unclosed quote.\n", 24);
		return (0);
	}
	str_parse = expand_str(data, str);
	if (str_parse == NULL)
		return (0);
	if (!create_token_list(data, str_parse))
	{
		free(str_parse);
		return (0);
	}
	//debug_tokens(data->begin);
	free(str_parse);
	return (1);
}

t_cmd	*parse_cmd(t_shell *data, t_token *token)
{
	t_cmd	*lst_cmd;
	t_cmd	*new_cmd;

	lst_cmd = NULL;
	while (token)
	{
		if (!token->prev || token->prev->type == PIPE)
		{
			new_cmd = create_cmd(data, token);
			if (!new_cmd)
			{
				free_cmd(&new_cmd);
				free_cmd(&lst_cmd);
				return (NULL);
			}
			if (!lst_cmd)
				lst_cmd = new_cmd;
			else
				add_cmd(&lst_cmd, new_cmd);
		}
		token = token->next;
	}
	return (lst_cmd);
}
