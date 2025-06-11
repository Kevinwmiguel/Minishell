/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:03:27 by joanda-s          #+#    #+#             */
/*   Updated: 2025/06/11 00:11:53 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

void	finish_expansion(t_shell *utils)
{
	int	i;

	i = 0;
	while (utils->splitex[i])
	{
		if (i == 0)
		{
			utils->output_ex = ft_strjoinn(utils->splitex[i], \
				utils->splitex[i + 1]);
			if (utils->splitex[i + 1] == NULL)
				i += 1;
			else
				i += 2;
		}
		else
		{
			utils->output_ex = ft_strjoinn(utils->output_ex, utils->splitex[i]);
			i++;
		}
	}
}

void	ex_expand_env(t_shell *utils, int i)
{
	utils->count_n = utils->count_m;
	while (ft_isalnum((int)utils->splitex[i][utils->count_n]) == 1)
		utils->count_n++;
	utils->splitex[i] = expand_env(utils->splitex[i], utils);
}

void	ex_splitex_dollars(t_shell *utils, int i)
{
	while (is_there_a_dollar(utils->splitex[i]) != 0)
	{
		utils->count_m = 0;
		while (utils->splitex[i][utils->count_m]
			&& utils->splitex[i][utils->count_m] != '$')
			utils->count_m++;
		utils->count_h = utils->count_m;
		if (utils->splitex[i][utils->count_m] == '$')
		{
			utils->count_m++;
			if (utils->splitex[i][utils->count_m] == '$')
			{
				utils->dollar = pid_dollar(utils->splitex[i], utils->count_m);
				if (utils->dollar % 2 != 0)
					utils->splitex[i] = expand_pid(utils->splitex[i],
							utils->count_m, utils);
				utils->count_m++;
			}
			else
				ex_expand_env(utils, i);
		}
	}
}

void	ex_splitex(t_shell *utils, int i)
{
	while (utils->splitex[i])
	{
		ex_splitex_dollars(utils, i);
		i++;
	}
	utils->count_var = 0;
}

char	*expansions(char *argv, t_shell *utils, int pa)
{
	int		i;

	utils->count_n = 0;
	utils->dollar = 0;
	wyw_start(utils);
	utils->splitex = ft_split2(argv, ' ');
	i = 0;
	utils->count_m = 0;
	utils->count_h = 0;
	if (pa == 2)
		return (free_dptr(utils->splitex), ft_strdup(argv));
	ex_splitex(utils, i);
	finish_expansion(utils);
	free_dptr(utils->splitex);
	return (utils->output_ex);
}
