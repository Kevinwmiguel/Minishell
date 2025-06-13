/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:06:35 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 23:46:34 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/builtins.h"

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

void	pick_path2(t_files *file, char **path, int cmd_idx, int path_idx)
{
	char	*tmp;

	tmp = ft_strjoin(path[path_idx], "/");
	if (!tmp)
	{
		path_cleaner(path);
		exit(EXIT_FAILURE);
	}
	file->cmds[cmd_idx][0] = ft_strjoin(tmp, file->cmds[cmd_idx][0]);
	free(tmp);
	if (!file->cmds[cmd_idx][0])
	{
		path_cleaner(path);
		exit(EXIT_FAILURE);
	}
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

char	*get_command_path(char *cmd)
{
	char	*paths[3];
	char	*full_path;
	int		i;

	i = 0;
	paths[0] = "/bin/";
	paths[1] = "/usr/bin/";
	paths[2] = NULL;
	while (paths[i])
	{
		full_path = malloc(strlen(paths[i]) + length2(cmd) + 1);
		if (!full_path)
		{
			perror("Erro de malloc");
			exit(1);
		}
		ft_strcpy(full_path, paths[i]);
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_directory_path(char *path)
{
	char	*last_slash;
	char	*dir_path;

	last_slash = ft_strrchr(path, '/');
	if (!last_slash)
		return (NULL);
	dir_path = malloc(last_slash - path + 2);
	if (!dir_path)
	{
		perror("Erro de malloc");
		exit(1);
	}
	ft_strncpy(dir_path, path, last_slash - path + 1);
	dir_path[last_slash - path + 1] = '\0';
	return (dir_path);
}