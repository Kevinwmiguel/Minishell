/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:19:11 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/09 19:02:17 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/builtins.h"

int	check_accessible(const char *path)
{
	if (access(path, F_OK) != 0)
	{
		perror("Arquivo/Diretório não encontrado");
		return (0);
	}
	if (access(path, R_OK) != 0)
	{
		perror("Sem permissão de leitura");
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		printf("leitura n da %s\n", path);
		return (0);
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	final_cleaner9(t_files *file)
{
	int	i;
	int	j;

	close_inout(file);
	if (file->cmds)
	{
		i = 0;
		while (i < file->cmd_count)
		{
			if (file->cmds[i])
			{
				j = 0;
				while (file->cmds[i][j])
				{
					free(file->cmds[i][j]);
					j++;
				}
				free(file->cmds[i]);
			}
			i++;
		}
		free(file->cmds);
	}
}
