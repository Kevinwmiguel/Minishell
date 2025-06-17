/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:59:57 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/18 00:20:41 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	update_pwd(t_shell *shell)
{
	char	cwd[4096];
	char	*new_pwd;
	int		i;

	if (!getcwd(cwd, sizeof(cwd)))
		return ;
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return ;
	i = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(new_pwd);
			break ;
		}
		i++;
	}
	i = 0;
	while (shell->exp && shell->exp[i])
	{
		if (ft_strncmp(shell->exp[i], "PWD=", 4) == 0)
		{
			free(shell->exp[i]);
			shell->exp[i] = ft_strdup(new_pwd);
			break ;
		}
		i++;
	}
	free(new_pwd);
}

void	build_pwd(t_shell *shell)
{
	char	cwd[4096];
	int		fd;

	fd = STDOUT_FILENO;
	// if (shell->cmd && shell->cmd->redirect && shell->cmd->redirect->pipe)
	// 	fd = shell->cmd->redirect->pipe->outfd;
	(void)shell;
	if (getcwd(cwd, 4096))
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
	}
}
