/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:48:21 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/19 21:52:36 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*create_export_line(const char *env_entry)
{
	char *equal = ft_strchr(env_entry, '=');
	char *name = NULL;
	char *value = NULL;
	char *tmp = NULL;
	char *result = NULL;
	if (!equal)
		return (ft_strjoin("declare -x ", env_entry));
	name = ft_substr(env_entry, 0, equal - env_entry + 1);
	if (!name)
		return (NULL);
	tmp = ft_strjoin("\"", equal + 1);
	if (!tmp)
		return (free(name), NULL);
	value = ft_strjoin(tmp, "\"");
	free(tmp);
	if (!value)
		return (free(name), NULL);
	tmp = ft_strjoin("declare -x ", name);
	free(name);
	if (!tmp)
		return (free(value), NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (result);
}

void	free_string(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i]);
	free(str);
}

char	**build_export(t_shell *shell)
{
	int i = 0;
	int j = 0;
	char **formatted;
	int size;
	if (!shell->env)
		return (NULL);
	size = mlc_size(0, shell->env);
	formatted = ft_calloc(size + 1, sizeof(char *));
	if (!formatted)
		return (NULL);
	while (shell->env[i])
	{
		formatted[j] = create_export_line(shell->env[i]);
		if (!formatted[j])
			break ;
		i++;
		j++;
	}
	formatted[j] = NULL;
	if (shell->env[i])
	{
		free_string(formatted);
		return (NULL);
	}
	return (formatted);
}

void	handle_export(t_shell *shell)
{
	int		i;

	i = 0;
	if (shell->cmd->args[1])
	{
		free_dptr(shell->exp);
		shell->exp = build_export(shell);
		if (!shell->exp)
			return ;
	}
	else
	{
		while (shell->exp[i])
		{
			write(1, shell->exp[i], ft_strlen(shell->exp[i]));
			write(1, "\n", 1);
			i++;
		}
	}
}
