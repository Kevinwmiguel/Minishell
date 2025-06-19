/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:58:50 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/19 19:16:38 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	build_echo(t_shell *shell, char **args)
{
	int	i;
	int	nl;
	int	fd;

	i = 1;
	nl = 1;
	fd = STDOUT_FILENO;
	if (shell->cmd && shell->cmd->redirect->outfd)
		fd = shell->cmd->redirect->outfd;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", fd);
}
