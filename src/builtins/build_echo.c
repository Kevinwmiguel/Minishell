/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:58:50 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/03 16:14:12 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	build_echo(t_shell *shell, char **args)
{
	int	i;
	int	nl;
	int	fd;

	(void)shell;
	i = 1;
	nl = 1;
	fd = STDOUT_FILENO;
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
	shell->exit_code = 0;
}
