/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:18:49 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/29 21:48:14 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	remove_all_double_left_tokens(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "<<", 3) == 0)
		{
			j = i;
			while (cmd->args[j + 2])
			{
				cmd->args[j] = cmd->args[j + 2];
				j++;
			}
			cmd->args[j] = NULL;
			cmd->args[j + 1] = NULL;
			continue ;
		}
		i++;
		k++;
	}
}

void	remove_one_left_tokens(t_cmd *cmd, int file_idx)
{
	int	i;

	i = file_idx - 1;
	while (cmd->args[i + 1])
	{
		cmd->args[i] = cmd->args[i + 1];
		i++;
	}
	cmd->args[i] = NULL;
}

void	handle_double_left(t_cmd *cmd)
{
	int	idx;
	int	idx_limiter;

	idx = 0;
	while ((find_next_double_left_index(cmd, idx)) != -1)
	{
		idx = find_next_double_left_index(cmd, idx);
		idx_limiter = idx + 1;
		if (!cmd->args[idx_limiter])
		{
			write(2, "Limite ausente para heredoc\n", 29);
			exit(1);
		}
		cmd->redirect->heredoc = here_doc(cmd->args[idx_limiter]);
		idx = idx_limiter;
	}
	remove_all_double_left_tokens(cmd);
}

void	handle_single_left(t_cmd *cmd)
{
	int	file_index;

	file_index = find_input_file_index(cmd->args, 0);
	if (file_index == -1)
	{
		write(2, "Arquivo não fornecido para redirecionamento\n", 45);
		exit(1);
	}
	cmd->redirect->infd = open(cmd->args[file_index], O_RDONLY);
	if (cmd->redirect->infd < 0)
	{
		perror("open");
		exit(1);
	}
	remove_one_left_tokens(cmd, file_index);
}

void	handle_redirection_left_input(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "<<", 3) == 0)
		{
			handle_double_left(cmd);
			i = 0;
			continue ;
		}
		else if (ft_strncmp(cmd->args[i], "<", 2) == 0)
		{
			handle_single_left(cmd);
			i = 0;
			continue ;
		}
		i++;
	}
}
