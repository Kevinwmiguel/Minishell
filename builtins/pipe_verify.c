/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_verify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:58:27 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 02:41:17 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	quotes_verify(char *argv)
{
	int	sq;
	int	dq;
	int	j;

	j = 0;
	sq = 0;
	dq = 0;
	while (argv[j] && argv[j] == ' ' && argv[j] == '\t' && argv[j] == '\n')
		j++;
	if (!argv[j])
		return (1);
	j = -1;
	while (argv[++j])
	{
		if (argv[j] == '\'')
			sq++;
		else if (argv[j] == '"')
			dq++;
	}
	if (dq % 2 != 0 || sq % 2 != 0)
	{
		write(1, "Odd number of quotes\n", 21);
		return (1);
	}
	return (0);
}

int	pipe_verify(char *argv, int x)
{
	int	j;

	j = -1;
	while (argv[++j])
	{
		x = 0;
		if (j == 0 && argv[j] == '|')
			return (ft_putendl_fd("wrong pipes", 1), -1);
		if (argv[j] == '|')
		{
			j++;
			if (!argv[j])
				return (ft_putendl_fd("wrong pipes", 1), -1);
			while (argv[j] && argv[j] != '|')
			{
				if (argv[j] != ' ')
					x++;
				j++;
			}
			if (x == 0)
				return (ft_putendl_fd("wrong pipes", 1), -1);
			j--;
		}
	}
	return (0);
}
