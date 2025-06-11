/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:56:23 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 02:47:21 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	in_between(char c, char *str, int i)
{
	int	x;

	x = 0;
	while (str[i + x] && str[i + x] != c)
		x++;
	return (x);
}

int	varlen(char *str, int k)
{
	while (str[k] && str[k] != '$')
		k++;
	return (k);
}

int	pid_dollar(char *str, int j)
{
	int	x;

	j--;
	if (j < 0)
		return (0);
	x = 0;
	while (j >= 0 && str[j] == '$')
	{
		x++;
		j--;
	}
	return (x);
}

char	*expand_pid(char *str, int j, t_shell *utils)
{
	char	*pid_str;
	char	*before;
	char	*after;
	char	*joined;

	(void)utils;
	pid_str = ft_getpid();
	before = ft_substr(str, 0, j - 2);
	after = ft_substr(str, j, ft_strlen(str) - j);
	joined = ft_strjoin(before, pid_str);
	str = ft_strjoin(joined, after);
	free(pid_str);
	return (str);
}

void	wyw_start(t_shell *utils)
{
	utils->o_que_quiser3 = NULL;
	utils->o_que_quiser4 = NULL;
	utils->o_que_quiser5 = NULL;
	utils->o_que_quiser2 = NULL;
}
