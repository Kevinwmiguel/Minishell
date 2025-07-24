/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:54:54 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 11:36:11 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static int	copy_export(char **dst, char **src, int index)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dst[index] = ft_strdup(src[i]);
		if (!dst[index])
			return (0);
		index++;
		i++;
	}
	return (index);
}

static int	append_export(char **dst, char **src, char **env, int index)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		if (!ft_strchr(src[i], '=') && !find_in_env(env, src[i]))
		{
			dst[index] = ft_strdup(src[i]);
			if (!dst[index])
				return (0);
			index++;
		}
		i++;
	}
	return (index);
}

char	**merge_exp_lists(char **old, char **new, char **env)
{
	char	**merged;
	int		count;
	int		i;

	count = mlc_size(0, old) + mlc_size(0, new);
	merged = ft_calloc(count + 1, sizeof(char *));
	if (!merged)
		return (NULL);
	i = copy_export(merged, new, 0);
	if (!i)
		return (free_split(merged), NULL);
	i = append_export(merged, old, env, i);
	if (!i)
		return (free_split(merged), NULL);
	merged[i] = NULL;
	return (merged);
}

char	*join_export(char *name, char *value)
{
	char	*full;

	full = ft_strjoin(name, value);
	if (!full)
		return (NULL);
	return (full);
}

void	handle_export(t_shell *shell, t_cmd_r *clean)
{
	int	i;
	int	fd;

	fd = STDOUT_FILENO;
	if (shell->cmd && shell->cmd->redirect && shell->cmd->redirect->outfd > 0)
		fd = shell->cmd->redirect->outfd;
	if (clean->args[1])
	{
		update_env_export(shell, clean->args + 1);
		return ;
	}
	i = 0;
	while (shell->exp[i])
	{
		write(fd, "declare -x ", 11);
		write(fd, shell->exp[i], ft_strlen(shell->exp[i]));
		write(fd, "\n", 1);
		i++;
	}
}
