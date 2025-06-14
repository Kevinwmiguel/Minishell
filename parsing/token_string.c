/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-14 15:38:46 by jmehmy            #+#    #+#             */
/*   Updated: 2025-06-14 15:38:46 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_quote_char(char c, bool *is_single_quote, bool *is_double_quote)
{
	if (c == '\'' && !(*is_single_quote) && !(*is_double_quote))
	{
		(*is_single_quote) = true;
		return (true);
	}
	else if (c == '\"' && !(*is_single_quote) && !(is_double_quote))
	{
		(*is_double_quote) = true;
		return (true);
	}
	else if (c == '\'' && (*is_single_quote) && !(is_double_quote))
	{
		(*is_single_quote) = false;
		return (true);
	}
	else if (c == '\"' && (*is_single_quote) && !(is_double_quote))
	{
		(*is_double_quote) = false;
		return (true);
	}
	return (false);
}

void	get_type(t_token *token)
{
	if (token->type == DOLLAR)
		return ;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = CMD;
	else
		token->type = ARG;
}

void	get_token_string(t_token *token, char **line)
{
	char	*str;
	bool	is_single_quote;
	bool	is_double_quote;

	str = *line;
	is_single_quote = false;
	is_double_quote = false;
	token->str = NULL;
	while (*str)
	{
		if (handle_quote_char(*str, &is_single_quote, &is_double_quote))
			;
		else if ((!is_double_quote && !is_single_quote) && (special_char(str)
				|| is_space(*str)))
		{
			if (!is_space(*str) && token->str == NULL)
				token->str = get_special_char(&str);
			break ;
		}
		else
			add_char(&token->str, *str);
		str++;
	}
	*line = str;
}
