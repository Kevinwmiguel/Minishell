/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:33:10 by thguimar          #+#    #+#             */
/*   Updated: 2025/06/11 02:42:50 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

int	equal_vars(char **exp, char **argv, int j, int flag)
{
	int	m;

	m = 0;
	while (exp[m + flag])
	{
		if (ft_strlen3(argv[j]) > ft_strlen3(exp[m]))
		{
			if (ft_strncmp(argv[j], exp[m], ft_strlen3(argv[j])) == 0)
				return (1);
			m++;
		}
		else
		{
			if (ft_strncmp(argv[j], exp[m], ft_strlen3(exp[m])) == 0)
				return (1);
			m++;
		}
	}
	return (0);
}

void	argc2(t_shell *utils, char **argv, int j, int argc)
{
	if (utils->pipe_bridge->redirection == false)
	{
		if (equal_vars(utils->exp, argv, j, 0) == 1)
		{
			if (is_there_equals(argv[j]) == 1)
			{
				utils->export->mlc = utils->exp;
				export_helper(utils->export, argv, j);
				utils->export->mlc = bubble_sort(0,
						utils->export->mlc, 1, argc);
			}
		}
		else
		{
			export_helper2(utils->exp, argv, j);
			utils->exp = bubble_sort(0, utils->exp, 1, argc);
		}
	}
}

char	**dptr_dup(char	**dptr)
{
	char	**rtn;
	int		i;

	i = -1;
	rtn = ft_calloc(sizeof(char *), mlc_size(0, dptr) + 1);
	while (dptr[++i])
		rtn[i] = ft_strdup(dptr[i]);
	return (rtn);
}

char	**build_export(int argc, char **argv, t_shell *utils)
{
	utils->export_j = 1;
	if (argc == 1)
	{
		utils->export->i = mlc_size(0, utils->exp);
		write_exp(utils);
	}
	else
	{
		if (utils->pipe_bridge->redirection == true)
			handle_redirection_right_input(utils->pipe_bridge);
		while (argv[utils->export_j])
		{
			utils->exp = bubble_sort(0, utils->exp, 1, argc);
			argc2(utils, argv, utils->export_j, argc);
			index_reset(utils);
			utils->export_j++;
		}
	}
	free_dptr(utils->envr);
	utils->envr = dptr_dup(utils->exp);
	return (utils->exp);
}
