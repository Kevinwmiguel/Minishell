/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:59:42 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 10:56:22 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	root_signal(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	is_illegal_file_read(t_cmd *cmd, t_pipexinfo *info)
{
	int	i;

	if (!cmd || !cmd->args || info->fd_in == 0)
		return (0);
	if (ft_strncmp(cmd->args[0], "cat", 4) != 0)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '<' && cmd->args[i][0] != '-')
			return (1);
		i++;
	}
	return (0);
}
