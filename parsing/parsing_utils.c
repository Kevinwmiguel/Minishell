/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:37:57 by jmehmy            #+#    #+#             */
/*   Updated: 2025/06/16 14:32:09 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

char	*my_get_env(t_shell *data, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (data->env[i])
	{
		if (ft_strncmp(var_name, data->env[i], len) == 0
			&& len_env(data->env[i]) == len)
			return (ft_strdup(data->env[i] + ft_strlen(var_name) + 1));
		i++;
	}
	return (NULL);
}

int	verify_closed_quote(char *str)
{
	int		i;
	bool	is_single_quote;
	bool	is_double_quote;
	i = 0;
	is_single_quote = false;
	is_double_quote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !is_single_quote && !is_double_quote)
			is_single_quote = true;
		else if (str[i] == '\"' && !is_single_quote && !is_double_quote)
			is_double_quote = true;
		else if (str[i] == '\'' && is_single_quote && !is_double_quote)
					is_single_quote = false;
		else if (str[i] == '\"' && is_double_quote && !is_single_quote)
			is_double_quote = false;
		i++;
	}
	if (is_single_quote || is_double_quote)
		return (1);
	return (0);
}

void	add_char(char **str, char c)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(*str) + 2));
	if (!dest)
		return ;
	while ((*str) && (*str)[i] != '\0')
	{
		dest[i] = (*str)[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	if (*str)
		free(*str);
	(*str) = dest;
}

void	add_cmd(t_cmd **list_cmd, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (*list_cmd == NULL)
	{
		*list_cmd = new_cmd;
		return ;
	}
	tmp = *list_cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}
