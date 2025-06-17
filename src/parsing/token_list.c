/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-14 15:38:20 by jmehmy            #+#    #+#             */
/*   Updated: 2025-06-14 15:38:20 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_last_token(t_token *token_list)
{
	while (token_list && token_list->next)
		token_list = token_list->next;
	return (token_list);
}

static bool	add_token(t_shell *data, char **str)
{
	t_token	*last_token;
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (false);
	token->type = 0;
	get_token_string(token, str);
	if (!token->str)
	{
		free(token);
		return (false);
	}
	token->prev = NULL;
	token->next = NULL;
	if (!data->begin)
		data->begin = token;
	else
	{
		last_token = ft_last_token(data->begin);
		token->prev = last_token;
		last_token->next = token;
	}
	return (true);
}

void	free_token_list(t_shell *data)
{
	t_token	*token;

	while (data->begin)
	{
		token = data->begin;
		if (data->begin->str)
			free(data->begin->str);
		data->begin = data->begin->next;
		if (token)
			free(token);
	}
}

bool	create_token_list(t_shell *data, char *str)
{
	data->begin = NULL;
	while (*str)
	{
		skip_space(&str);
		if (add_token(data, &str))
			get_type(ft_last_token(data->begin));
		else
		{
			if (*str)
				return (false);
		}
	}
	return (true);
}
