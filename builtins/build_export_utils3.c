/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:12:42 by thguimar          #+#    #+#             */
/*   Updated: 2025/06/11 02:47:34 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

void	export_hha(char **argv, t_builtvars *export, int j, int flag)
{
	while (export->l < (int)ft_strlen(argv[j]) && argv[j][export->l] != '=')
	{
		export->mlc[export->m][export->l] = argv[j][export->l];
		export->l++;
	}
	if (flag == 1)
		export->n = ft_strlen3(export->mlc[export->m]);
}

int	line_waste(t_builtvars *export, char **argv, int flag, int j)
{
	int	i;

	i = 0;
	free(export->mlc[export->m]);
	if (flag == 0)
		export->mlc[export->m] = \
		ft_calloc(ft_strlen(argv[export->j]) + 1, sizeof(char));
	if (flag == 1)
		export->mlc[export->i] = \
		ft_calloc(ft_strlen(argv[export->j]) + 1, sizeof(char));
	if (j >= 0)
	{
		while (argv[j][i++])
		{
			if (argv[j][i] == '=')
				flag = 1;
		}
	}
	return (flag);
}

void	export_helper_helper(t_builtvars *export, char **argv, int j)
{
	int	flag;

	flag = line_waste(export, argv, 0, j);
	export->l = 0;
	if (flag == 1)
		export_hha(argv, export, j, flag);
	else
		export->n = ft_strlen(export->mlc[export->m]);
	if (argv[j][export->l] != '"' && flag == 1)
		export->n++;
	while (argv[j][export->l + 1] == '"')
		export->l++;
	while (argv[j][export->l])
	{
		if (argv[j][export->l] != '"')
		{
			export->mlc[export->m][export->n] = argv[j][export->l];
			export->n++;
		}
		export->n++;
		export->l++;
	}
}

int	is_there_a_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
