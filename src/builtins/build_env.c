/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:36:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/17 19:23:51 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	ft_strcmp_ignore_quotes(char *s1, char *s2)
{
	int	i;

	if (cmp_names(s1, s2) != 0)
		return (1);
	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	if (!s1[i] || !s2[i])
		return (1);
	return (cmp_values(s1 + i + 1, s2 + i + 1));
}

int	ft_strcmp2(char *s1, char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	compare_exp_env(t_shell *shell, int i, int j)
{
	while (shell->env[i])
	{
		if (ft_strcmp_ignore_quotes(shell->exp[j], shell->env[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	write_exp_to_env(t_shell *shell, int j, int i)
{
	while (j > -1)
	{
		while (shell->exp[j][i])
		{
			if (shell->exp[j][i] == '=' && compare_exp_env(shell, 0, j) == 1)
			{
				ft_putstr_fd(shell->exp[j], 1);
				ft_putstr_fd("\n", 1);
				break ;
			}
			i++;
		}
		j--;
		i = 0;
	}
}

void	build_env(t_shell *shell)
{
	int	j;
	int	i;

	j = 0;
	while (shell->env && shell->env[j])
	{
		ft_putstr_fd(shell->env[j], 1);
		ft_putstr_fd("\n", 1);
		j++;
	}
	j = mlc_size(0, shell->exp) - 1;
	i = 0;
	write_exp_to_env(shell, j, i);
}
