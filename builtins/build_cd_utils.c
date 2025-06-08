/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:58 by thguimar          #+#    #+#             */
/*   Updated: 2025/06/04 18:50:45 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	get_line_value(char **exp, int line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_strlen3(exp[line]);
	while (exp[line][++i])
		j++;
	return (j);
}

void	get_cd(t_cd *cd, char **argv)
{
	cd->x = var_equal_line2(cd->utils->exp, "PWD=");
	cd->x = get_line_value(cd->utils->exp, cd->x);
	chdir(getcwd(argv[1], cd->x + ft_strlen(argv[1])));
	cd->flag = 1;
}

void	argc_2(t_cd *cd, char **argv)
{
	cd->i = 0;
	cd->j = 1;
	if (chdir(argv[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd("\n", 1);
	}
	else if (is_twopoints(argv[1]) == 0)
	{
		if (argv[1][cd->i] == '/')
		{
			cd->str = ft_calloc(ft_strlen(argv[1]) + 1, sizeof(char));
			cd->str[cd->j - 1] = argv[1][cd->i];
			cd->i++;
		}
		else
		{
			cd->str = ft_calloc(ft_strlen(argv[1]) + 1, sizeof(char));
			cd->str[0] = '/';
		}
		while (argv[1][cd->i])
			cd->str[cd->j++] = argv[1][cd->i++];
		get_cd(cd, argv);
	}
}

void	argc_1(t_cd *cd, char *home, int argc, char **argv)
{
	cd->i = 0;
	while (argc == 1 || (argv[1][cd->i] == 47 && argv[1][cd->i]))
	{
		cd->i++;
		if (argc == 1)
		{
			chdir(home);
			break ;
		}
		if (argv[1][cd->i] == '\0')
		{
			chdir("/");
			break ;
		}
	}
}

int	builtin_not_command(char **argv)
{
	if (ft_strcmp2("echo", argv[0]) == 0)
		return (1);
	else if (ft_strcmp2("cd", argv[0]) == 0)
		return (1);
	else if (ft_strcmp2("pwd", argv[0]) == 0)
		return (1);
	else if (ft_strcmp2("export", argv[0]) == 0)
		return (1);
	else if (ft_strcmp2("unset", argv[0]) == 0)
		return (1);
	else if (ft_strcmp2("exit", argv[0]) == 0)
		return (1);
	else if (ft_strcmp2("env", argv[0]) == 0)
		return (1);
	return (0);
}
