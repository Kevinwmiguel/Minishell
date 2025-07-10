/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:31:38 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/10 16:27:51 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	h_lines(char **args, t_shell *shell)
{
	int	status;

	status = ft_atoi(args[1]);
	shell->exit_code = status;
	free_token_list(shell);
	final_cleaner(shell);
	exit(status);
}

void	freedom(t_shell *shell)
{
	free_token_list(shell);
	final_cleaner(shell);
	close_extra_fds();
}

void	build_exit(t_shell *shell)
{
	char	**args;
	int		i;
	int		code;

	args = shell->cmd->args;
	code = shell->exit_code;
	i = 0;
	if (!args[1])
	{
		freedom(shell);
		exit(code);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putendl_fd("numeric argument required", STDERR_FILENO);
			freedom(shell);
			exit(2);
		}
		i++;
	}
	h_lines(args, shell);
}
