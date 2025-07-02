/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:37:35 by jmehmy            #+#    #+#             */
/*   Updated: 2025/07/01 11:34:01 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_search(char **line)
{
	char	*str;
	char	*expand_search;

	expand_search = NULL;
	str = *line;
	while (*str && (*str != '\'' && *str != '\"' && *str != '$')
		&& (!special_char(str)) && !is_space(*str))
	{
		add_char(&expand_search, *str);
		str++;
	}
	*line = str;
	return (expand_search);
}

static char	*get_expand_value(t_shell *data, char *get_search)
{
	char	*expand_value;

	expand_value = NULL;
	if (get_search)
	{
		expand_value = my_get_env(data, get_search);
		if (!expand_value)
			expand_value = ft_strdup("");
		free(get_search);
	}
	else
		expand_value = ft_strdup("$");
	return (expand_value);
}

static char	*expand_result(t_shell *data, char **line, bool is_double_quote)
{
	char	*expand_value;
	char	*str;

	str = *line;
	expand_value = NULL;
	str++;
	if (*str == '\'' || (*str == '\"' && !is_double_quote))
	{
		*line = str;
		return ("");
	}
	if (*str == '?')
	{
		expand_value = ft_itoa(data->exit_code);
		str++;
	}
	else if (*str == '$')
	{
		expand_value = ft_getpid();
		str++;
	}
	else
		expand_value = get_expand_value(data, get_search(&str));
	*line = str;
	return (expand_value);
}

void	join_expand(t_shell *data, char **result, char **str,
		bool is_double_quote)
{
	char	*tmp[2];

	tmp[0] = expand_result(data, str, is_double_quote);
	tmp[1] = ft_strjoin(*result, tmp[0]);
	if (*result)
		free(*result);
	if (tmp[0])
		free(tmp[0]);
	*result = tmp[1];
}

char	*expand_str(t_shell *data, char *str)
{
	char	*result;
	bool	is_single_quote;
	bool	is_double_quote;
	bool	expand_exec;

	is_single_quote = false;
	is_double_quote = false;
	result = ft_strdup("");
	while (*str)
	{
		expand_exec = false;
		handle_quote_char(*str, &is_single_quote, &is_double_quote);
		if (*str == '$' && (*(str + 1) && (*(str + 1) != '\'' && *(str
						+ 1) != '\"')) && !is_single_quote)
		{
			expand_exec = true;
			join_expand(data, &result, &str, is_double_quote);
		}
		else
			add_char(&result, *str);
		if (!expand_exec)
			str++;
	}
	return (result);
}
