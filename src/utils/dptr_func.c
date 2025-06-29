/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dptr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 21:28:50 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/29 21:31:06 by kwillian         ###   ########.fr       */
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
