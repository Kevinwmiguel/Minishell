/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:00:33 by thguimar          #+#    #+#             */
/*   Updated: 2025/06/11 14:21:12 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	var_equal_line(char **env, char **argv, int j)
{
	int	m;

	m = 0;
	while (env[m])
	{
		if (ft_strncmp(argv[j], env[m], ft_strlen3(argv[j])) == 0)
			return (m);
		m++;
	}
	return (0);
}

int	ft_strlen3(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	is_there_equals(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	write_exp2(t_shell *utils, int flag, int j, int i)
{
	int	flag2;

	flag2 = 0;
	while (utils->exp[j][i])
	{
		if (i != 0 && utils->exp[j][i - 1] == '=' && flag == 0)
		{
			flag = 1;
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd(utils->exp[j][i], 1);
		i++;
		if (flag == 1 && utils->exp[j][i] == '\0')
		{
			ft_putchar_fd('"', 1);
			flag = 0;
			flag2 = 1;
		}
	}
	return (flag2);
}

void	write_exp(t_shell *utils)
{
	int	j;
	int	i;
	int	flag;
	int	flag2;

	j = 0;
	i = 0;
	flag = 0;
	flag2 = 0;
	while (utils->exp[j])
	{
		ft_putstr_fd("declare -x ", 1);
		flag2 = write_exp2(utils, flag, j, i);
		if (flag2 == 0 && is_there_equals(utils->exp[j]) == 1)
		{
			ft_putchar_fd('"', 1);
			ft_putchar_fd('"', 1);
		}
		ft_putstr_fd("\n", 1);
		i = 0;
		j++;
	}
}
