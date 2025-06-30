/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:31:38 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/30 22:32:49 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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
	status = ft_atoi(args[1]);
	free_token_list(shell);
	final_cleaner(shell);
	exit(status);
}
