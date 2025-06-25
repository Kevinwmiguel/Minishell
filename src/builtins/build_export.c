/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:48:21 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/25 18:46:11 by kwillian         ###   ########.fr       */
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
		return (free(value), free(tmp), NULL);
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

// void	handle_export(t_shell *shell)
// {
// 	int		i;

// 	i = 0;
// 	if (shell->cmd->args[1])
// 	{
// 		free_dptr(shell->exp);
// 		shell->exp = build_export(shell);
// 		if (!shell->exp)
// 			return ;
// 	}
// 	else
// 	{
// 		while (shell->exp[i])
// 		{
// 			write(1, shell->exp[i], ft_strlen(shell->exp[i]));
// 			write(1, "\n", 1);
// 			i++;
// 		}
// 	}
// }

int	dptr_len(char **ptr)
{
	int	i = 0;

	while (ptr && ptr[i])
		i++;
	return (i);
}

char	**dptr_dup_add(char **env, char *new_entry)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (dptr_len(env) + 2));
	if (!copy)
		return (NULL);
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
			return (free_dptr(copy), NULL);
		i++;
	}
	copy[i++] = ft_strdup(new_entry);
	copy[i] = NULL;
	return (copy);
}


char	**dptr_dup_replace(char **env, char *new_entry, int index)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (dptr_len(env) + 1));
	if (!copy)
		return (NULL);
	while (env[i])
	{
		if (i == index)
			copy[i] = ft_strdup(new_entry);
		else
			copy[i] = ft_strdup(env[i]);
		if (!copy[i])
			return (free_dptr(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
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
		if (ft_strncmp(env[i], new_entry, ft_strchr(new_entry, '=') - new_entry + 1) == 0)
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


void	update_env_export(t_shell *shell)
{
	int		i;
	char	**tmp;

	i = 1;
	while (shell->cmd->args[i])
	{
		if (is_valid_identifier(shell->cmd->args[i]))
		{
			if (ft_strchr(shell->cmd->args[i], '='))
			{
				tmp = add_or_replace_env(shell->env, shell->cmd->args[i]);
				if (!tmp)
					return ;
				free_dptr(shell->env);
				shell->env = tmp;
			}
		}
		i++;
	}
	free_dptr(shell->exp);
	shell->exp = build_export(shell);
}


void	handle_export(t_shell *shell)
{
	int		i;

	i = 0;
	if (shell->cmd->args[1])
	{
		update_env_export(shell);
		return ;
	}
	while (shell->exp[i])
	{
		write(1, shell->exp[i], ft_strlen(shell->exp[i]));
		write(1, "\n", 1);
		i++;
	}
}
