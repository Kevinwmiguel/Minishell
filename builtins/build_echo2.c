/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:05:30 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 02:49:12 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	echo_flag(char *argv)
{
	int	i;

	i = 1;
	if (ft_strncmp("-n", argv, 2) == 0)
	{
		while (argv[i] && argv[i] != ' ')
		{
			if (argv[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	flag_count(char *argv)
{
	int	i;

	i = 1;
	while (argv[i] == 'n')
		i++;
	while (argv[i] == ' ')
		i++;
	return (i);
}

int	final_reader_size(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[i] != '\'')
				i++;
		else if (str[i] == '"')
			while (str[i] != '"')
				i++;
		else
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
		if (str[i] == '\'' || str[i] == '"')
			i++;
		x++;
	}
	return (x);
}

char	*remove_before_last_echo(char *str)
{
	char	*last_echo;
	char	*after_echo;
	char	*result;

	last_echo = ft_strrstr(str, " echo");
	if (!last_echo)
		return (ft_strdup(str));
	after_echo = last_echo + 5;
	while (*after_echo == ' ' || *after_echo == '\t')
		after_echo++;
	result = ft_strdup(last_echo + 5);
	return (result);
}

char	*remove_after_last_cat(char *str)
{
	char	*last_cat;
	char	*result;

	last_cat = ft_strrstr(str, " cat");
	if (!last_cat)
		return (ft_strdup(str));
	result = ft_substr(str, 0, last_cat - str);
	return (result);
}

// char	*remove_before_last_echo(char *str)
// {
// 	char	*last_echo;
// 	char	*result;
// 	last_echo = ft_strrstr(str, " echo ");
// 	if (!last_echo)
// 	{
// 		result = ft_strdup(str);
// 		return (result);
// 	}
// 	free(str);
// 	result = ft_strdup(last_echo + 5);
// 	return (result);
// }