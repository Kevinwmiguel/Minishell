/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:05:28 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 20:35:51 by kwillian         ###   ########.fr       */
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

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*path_var = NULL;
	char	*fullpath = NULL;
	char	**paths;

	i = 0;
	fullpath = ft_strdup(cmd);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_var)
		return (fullpath);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (fullpath);
	i = 0;
	while (paths[i])
	{
		char *dir = ft_strjoin(paths[i], "/");
		char *candidate = ft_strjoin(dir, cmd);
		free(dir);

		if (access(candidate, X_OK) == 0)
		{
			free(fullpath);
			ft_free_split(paths);
			return (candidate);
		}

		free(candidate);
		i++;
	}

	ft_free_split(paths);
	return (fullpath);
}
