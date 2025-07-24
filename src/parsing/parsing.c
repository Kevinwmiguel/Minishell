/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:08 by jmehmy            #+#    #+#             */
/*   Updated: 2025/07/24 11:27:08 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_shell *data, t_token *token)
{
	t_cmd	*cmd;

	(void)data;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->args = get_cmd(token);
	cmd->next = NULL;
	cmd->redirect = NULL;
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
		write(2, "Error: Unclosed quote.\n", 24);
		data->exit_code = 2;
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
	free(str_parse);
	return (1);
}

static int	handle_new_cmd(t_shell *data, t_token *token, t_cmd **lst)
{
	t_cmd	*new;

	new = create_cmd(data, token);
	if (!new)
	{
		free_cmd(&new);
		free_cmd(lst);
		return (0);
	}
	if (!*lst)
		*lst = new;
	else
		add_cmd(lst, new);
	return (1);
}

t_cmd	*parse_cmd(t_shell *data, t_token *token)
{
	t_cmd	*lst_cmd;

	lst_cmd = NULL;
	while (token)
	{
		if (token->type == PIPE && (!token->prev || token->prev->type == PIPE))
		{
			printf("invalid use of pipe '|'\n");
			data->exit_code = 1;
			return (NULL);
		}
		if (!token->prev || token->prev->type == PIPE)
		{
			if (!handle_new_cmd(data, token, &lst_cmd))
				return (NULL);
		}
		token = token->next;
	}
	return (lst_cmd);
}
