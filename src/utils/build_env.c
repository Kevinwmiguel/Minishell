/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:36:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 02:19:59 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

int	compare_exp_env(t_shell *utils, int i, int j)
{
	while (utils->env[i])
	{
		if (ft_strcmp2(utils->exp[j], utils->env[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	write_exp_to_env(t_shell *utils, int j, int i)
{
	while (j > -1)
	{
		while (utils->exp[j][i])
		{
			if (utils->exp[j][i] == '=' && compare_exp_env(utils, 0, j) == 1)
			{
				ft_putstr_fd(utils->exp[j], 1);
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
	int	fd;

	j = 0;
	fd = STDOUT_FILENO;
	if (shell->cmd && shell->cmd->redirect && shell->cmd->redirect->pipe)
		fd = shell->cmd->redirect->pipe->outfd;

	while (shell->env && shell->env[j])
	{
		ft_putstr_fd(shell->env[j], fd);
		ft_putstr_fd("\n", fd);
		j++;
	}
	write_exp_to_env(shell, fd, mlc_size(0, shell->exp) - 1);
}
