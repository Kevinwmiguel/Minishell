/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-14 15:36:46 by jmehmy            #+#    #+#             */
/*   Updated: 2025-06-14 15:36:46 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mlc_size(int j, char **mlc)
{
	while (mlc[j])
		j++;
	return (j);
}

char	**dptr_dup(char **dptr)
{
	char **rtn;
	int i;

	i = -1;
	rtn = ft_calloc(sizeof(char *), mlc_size(0, dptr) + 1);
	while (dptr[++i])
		rtn[i] = ft_strdup(dptr[i]);
	return (rtn);
}