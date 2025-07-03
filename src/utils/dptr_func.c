/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dptr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 21:28:50 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/03 13:30:05 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

char	*ft_getpid(void)
{
	char		*pid;
	int			fd;
	char		**temp;

	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
		return (NULL);
	pid = get_next_line(fd);
	if (!pid)
		return (NULL);
	temp = ft_split(pid, ' ');
	free(pid);
	if (!temp)
		return (NULL);
	pid = ft_strdup(temp[0]);
	free_split(temp);
	if (!pid)
		return (NULL);
	return (pid);
}
