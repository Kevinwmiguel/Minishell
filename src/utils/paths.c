/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:05:28 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/19 19:08:28 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = NULL;
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	*find_in_path(char **paths, char *cmd, char *fallback)
{
	int		i;
	char	*dir;
	char	*candidate;

	i = 0;
	while (paths[i])
	{
		dir = ft_strjoin(paths[i], "/");
		candidate = ft_strjoin(dir, cmd);
		free(dir);
		if (access(candidate, X_OK) == 0)
		{
			ft_free_split(paths);
			free(fallback);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	ft_free_split(paths);
	return (fallback);
}

char	*get_path(char *cmd, char **env)
{
	char	*fullpath;
	char	*path_var;
	char	**paths;
	int		i;

	fullpath = ft_strdup(cmd);
	path_var = NULL;
	i = 0;
	while (env[i] && !path_var)
		if (!ft_strncmp(env[i++], "PATH=", 5))
			path_var = env[i - 1] + 5;
	if (!path_var)
		return (fullpath);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (fullpath);
	return (find_in_path(paths, cmd, fullpath));
}
