/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:24:33 by thiago-camp       #+#    #+#             */
/*   Updated: 2025/06/11 00:11:47 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	unset_argv_checker(char *exp, char **argv)
{
	int	j;

	j = 0;
	while (argv[j])
	{
		if (ft_strncmp(exp, argv[j], ft_strlen4(argv[j])) == 0)
			return (1);
		j++;
	}
	return (0);
}

int	unset_flag(int flag, char *exp, char *argv)
{
	int	sla;

	sla = ft_strncmp(exp, argv, ft_strlen4(argv));
	if (sla == 0)
		flag++;
	return (flag);
}

char	**build_unset(int argc, char **argv, char **exp, int i)
{
	int		j;
	char	**copy;
	int		flag;

	j = -1;
	flag = 0;
	if (argc > 1)
	{
		while (argv[++j])
		{
			while (exp[++i])
				flag = unset_flag(flag, exp[i], argv[j]);
			i = -1;
		}
		j = -1;
		copy = ft_calloc(mlc_size(0, exp) - flag + 1, sizeof(char *));
		while (exp[++i])
		{
			if (unset_argv_checker(exp[i], argv) == 0)
				copy[++j] = ft_strdup(exp[i]);
		}
		free_dptr(exp);
		exp = copy;
	}
	return (exp);
}
