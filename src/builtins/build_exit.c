/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:31:38 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/03 16:25:01 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	h_lines(int status, char **args, t_shell *shell)
{
	status = ft_atoi(args[1]);
	free_token_list(shell);
	final_cleaner(shell);
	exit(status);
}

void	build_exit(t_shell *shell)
{
	char	**args;
	int		status;
	int		i;

	args = shell->cmd->args;
	status = 0;
	i = 0;
	if (!args[1])
	{
		free_token_list(shell);
		final_cleaner(shell);
		exit(0);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putendl_fd("numeric argument required", STDERR_FILENO);
			free_token_list(shell);
			final_cleaner(shell);
			exit(2);
		}
		i++;
	}
	h_lines(status, args, shell);
}
