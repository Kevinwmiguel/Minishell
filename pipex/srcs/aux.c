/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:44:56 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/01 18:14:32 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/builtins.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

char	**add_file_to_cmd(char **cmd, char *file_path)
{
	char	**new_cmd;
	int		i;

	i = 0;
	while (cmd[i] != NULL)
		i++;
	new_cmd = malloc((i + 2) * sizeof(char *));
	if (!new_cmd)
	{
		perror("Erro de malloc");
		exit(1);
	}
	i = 0;
	while (cmd[i] != NULL)
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	new_cmd[i] = file_path;
	new_cmd[i + 1] = NULL;
	return (new_cmd);
}

int	find_next_double_left_index(t_pipesort *piped, int start)
{
	int	i;

	i = start;
	while (piped->content[i])
	{
		if (ft_strncmp(piped->content[i], "<<", 3) == 0 && \
			ft_strlen(piped->content[i]) == 2)
			return (i);
		i++;
	}
	return (-1);
}
