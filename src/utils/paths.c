/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:05:28 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/29 21:59:25 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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
			free_split(paths);
			free(fallback);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	free_split(paths);
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

char	*checker_path(t_shell *shell, char **paths, char *tmp)
{
	char	*fullpath;
	int		i;

	i = 0;
	fullpath = NULL;
	if (shell->cmd->args[0][0] == '.' || shell->cmd->args[0][0] == '/')
	{
		if (access(shell->cmd->args[0], X_OK) == 0)
			return (ft_strdup(shell->cmd->args[0]));
		else
			return (NULL);
	}
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpath = ft_strjoin(tmp, shell->cmd->args[0]);
		free(tmp);
		if (access(fullpath, X_OK) == 0)
			break ;
		free(fullpath);
		fullpath = NULL;
		i++;
	}
	return (fullpath);
}

void	path_cleaner(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		if (i == 0)
			free(paths[i] - 5);
		else
			free(paths[i]);
		i++;
	}
	if (paths)
		free(paths);
}

char	**pick_path(char **envp)
{
	char	**path;
	int		index;

	index = 0;
	path = NULL;
	while (envp && envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			path = ft_split(envp[index], ':');
			if (!path)
				path_cleaner(path);
			else
				path[0] = path[0] + 5;
			break ;
		}
		index++;
	}
	return (path);
}
