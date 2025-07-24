/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 21:35:38 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 11:36:32 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	**add_or_replace_exp(char **exp, char *new_entry)
{
	int		i;
	size_t	key_len;
	char	*eq;

	eq = ft_strchr(new_entry, '=');
	if (eq)
		key_len = eq - new_entry;
	else
		key_len = ft_strlen(new_entry);
	i = 0;
	while (exp && exp[i])
	{
		if (ft_strncmp(exp[i], new_entry, key_len) == 0
			&& exp[i][key_len] == '=')
			return (dptr_dup_replace(exp, new_entry, i));
		i++;
	}
	return (dptr_dup_add(exp, new_entry));
}

char	**add_or_replace_env(char **env, char *new_entry)
{
	int		i;
	size_t	len;
	char	**new_env;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	while (env[i])
	{
		if (ft_strncmp(env[i], new_entry, ft_strchr(new_entry, '=') - new_entry
				+ 1) == 0)
		{
			new_env = dptr_dup_replace(env, new_entry, i);
			return (new_env);
		}
		i++;
	}
	return (dptr_dup_add(env, new_entry));
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	cmp_names(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != '=' || s2[i] != '=')
		return (s1[i] - s2[i]);
	return (0);
}

int	cmp_values(char *v1, char *v2)
{
	int	i;

	i = 0;
	if (v1[0] == '"')
		v1++;
	if (v2[0] == '"')
		v2++;
	while (v1[i] && v2[i])
	{
		if (v1[i] != v2[i])
			return (v1[i] - v2[i]);
		i++;
	}
	if ((v1[i] == '"' && v2[i] == '\0') || (v2[i] == '"' && v1[i] == '\0'))
		return (0);
	return (v1[i] - v2[i]);
}
