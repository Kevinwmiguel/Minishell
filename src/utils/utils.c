/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:13:18 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/05 20:52:13 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	free_dptr(char **dptr)
{
	int	i;

	i = 0;
	if (!dptr)
		return ;
	while (dptr[i])
	{
		free(dptr[i]);
		i++;
	}
	free(dptr);
}

int	mlc_size(int j, char **mlc)
{
	while (mlc[j])
		j++;
	return (j);
}

static int	count_strings(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char	**dptr_dup(char **arr)
{
	char	**copy;
	int		i;
	int		len;

	if (!arr)
		return (NULL);
	len = count_strings(arr);
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[len] = NULL;
	return (copy);
}

int	dptr_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
		i++;
	return (i);
}
