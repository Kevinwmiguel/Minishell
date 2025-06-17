/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-14 15:37:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025-06-14 15:37:13 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || (c >= 9 && c <= 13)))
		return (true);
	return (false);
}

void	skip_space(char **line)
{
	char	*str;

	str = *line;
	while (is_space(*str))
		str++;
	*line = str;
}

bool	special_char(char *str)
{
	if (str && ft_strlen(str) >= 2)
	{
		if (ft_strncmp(str, "<<", 2) == 0)
			return (true);
		else if (ft_strncmp(str, ">>", 2) == 0)
			return (true);
	}
	if (str && ft_strlen(str) >= 1)
	{
		if (ft_strncmp(str, "<", 1) == 0)
			return (true);
		else if (ft_strncmp(str, ">", 1) == 0)
			return (true);
		else if (ft_strncmp(str, "|", 1) == 0)
			return (true);
	}
	return (false);
}

char	*get_special_char(char **str)
{
	char	*s_char;

	s_char = NULL;
	if (ft_strncmp(*str, "<<", 2) == 0)
		s_char = ft_strdup("<<");
	else if (ft_strncmp(*str, ">>", 2) == 0)
		s_char = ft_strdup(">>");
	else if (ft_strncmp(*str, "<", 1) == 0)
		s_char = ft_strdup("<");
	else if (ft_strncmp(*str, ">", 1) == 0)
		s_char = ft_strdup(">");
	else if (ft_strncmp(*str, "|", 1) == 0)
		s_char = ft_strdup("|");
	*str = (*str) + ft_strlen(s_char);
	return (s_char);
}
