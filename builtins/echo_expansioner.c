/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_expansioner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:38:35 by thiago-camp       #+#    #+#             */
/*   Updated: 2025/06/11 02:41:59 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"
#include "../libft/libft.h"

bool	is_only_pipe(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (false);
	while (str[++i])
	{
		if (str[i] != '|')
			return (false);
	}
	return (true);
}

bool	is_there_pipe(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (false);
	while (str[++i])
	{
		if (str[i] == '|')
			return (true);
	}
	return (false);
}

int	size_before_pipe(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	return (i);
}

char	**pipping_commands2(char *str, int x)
{
	char	**rtn;

	(void)x;
	rtn = ft_split(str, '|');
	return (rtn);
}

char	**pipping_commands(char *input)
{
	int		i;
	int		x;
	char	**rtn;

	i = -1;
	x = 1;
	while (input[++i])
	{
		if (input[i] == '|')
			x++;
	}
	i = -1;
	rtn = pipping_commands2(input, x);
	return (rtn);
}
