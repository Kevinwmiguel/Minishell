/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:48:21 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 18:18:23 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static char	*build_quoted_value(const char *val)
{
	char	*quoted;
	char	*tmp;

	tmp = ft_strjoin("\"", val);
	if (!tmp)
		return (NULL);
	quoted = ft_strjoin(tmp, "\"");
	free(tmp);
	if (!quoted)
		return (NULL);
	return (quoted);
}

char	*create_export_line(const char *env_entry)
{
	char	*equal;
	char	*name;
	char	*value;
	char	*result;

	equal = ft_strchr(env_entry, '=');
	if (!equal)
	{
		equal = ft_strjoin("", env_entry);
		return (equal);
	}
	name = ft_substr(env_entry, 0, equal - env_entry + 1);
	if (!name)
		return (NULL);
	value = build_quoted_value(equal + 1);
	if (!value)
		return (free(name), NULL);
	result = join_export(name, value);
	free(name);
	free(value);
	return (result);
}

static char	**alloc_export_array(t_shell *shell)
{
	int		size;
	char	**formatted;

	size = mlc_size(0, shell->env);
	formatted = ft_calloc(size + 1, sizeof(char *));
	if (!formatted)
		return (NULL);
	return (formatted);
}

static int	fill_export_array(char **formatted, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!is_valid_identifier(env[i]))
		{
			i++;
			continue ;
		}
		formatted[j] = create_export_line(env[i]);
		if (!formatted[j])
			break ;
		i++;
		j++;
	}
	formatted[j] = NULL;
	if (env[i])
	{
		free_split(formatted);
		return (0);
	}
	return (1);
}

char	**build_export(t_shell *shell)
{
	char	**formatted;
	int		success;

	if (!shell->env)
		return (NULL);
	formatted = alloc_export_array(shell);
	if (!formatted)
		return (NULL);
	success = fill_export_array(formatted, shell->env);
	if (!success)
		return (NULL);
	return (formatted);
}
