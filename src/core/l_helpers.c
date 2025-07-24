/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:33:29 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 18:22:45 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	check_duplicate_var_exist(char **env, const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	line_helper(t_pipexinfo *info)
{
	info->fd[0] = -1;
	info->fd[1] = -1;
}

void	line_helper2(t_pipexinfo *info)
{
	if (info->fd[1] != -1)
		close(info->fd[1]);
	if (info->fd_in != STDIN_FILENO)
		close(info->fd_in);
}

void	export_print(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

void	close_extra_fds(void)
{
	int	i;

	i = 3;
	while (i <= 20)
	{
		close(i);
		i++;
	}
}
