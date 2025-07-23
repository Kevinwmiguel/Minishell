/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:18:49 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/16 21:34:18 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	remove_all_double_left_tokens(t_cmd *cmd)
{
	int	i;
	int	j;

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

void	handle_double_left(t_cmd *cmd, t_shell *shell)
{
	int	idx;
	int	idx_limiter;

	idx = 0;
	idx = find_next_double_left_index(cmd, idx);
	while (idx != -1)
	{
		idx_limiter = idx + 1;
		if (!cmd->args[idx_limiter])
		{
			write(2, "Limite ausente para heredoc\n", 29);
			exit(1);
		}
		int fd = here_doc(shell, cmd->args[idx_limiter]);
		if(fd == -1)
		{
			shell->exit_code = 130;
			shell->flag = 1;
			return ;
		}
		cmd->redirect->heredoc = fd;
		idx = idx_limiter + 1;
		idx = find_next_double_left_index(cmd, idx);
	}
}

void	handle_single_left(t_cmd *cmd, t_shell *shell)
{
	int	file_index;

	(void)shell;
	file_index = find_input_file_index(cmd->args, 0);
	if (file_index == -1)
	{
		write(2, "Arquivo não fornecido para redirecionamento\n", 45);
		exit(1);
	}
	cmd->redirect->infd = open(cmd->args[file_index], O_RDONLY);
	if (cmd->redirect->infd < 0)
	{
		perror(cmd->args[file_index]);
		exit(1);
	}
}

void	handle_redirection_left_input(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (find_next_double_left_index(cmd, 0) != -1)
	{
		handle_double_left(cmd, shell);
		if(shell->flag)
		{
			shell->exit_code = 130;
			return ;
		}
	}
	i = 0;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "<", 2) == 0 && \
		ft_strlen(cmd->args[i]) == 1)
			handle_single_left(cmd, shell);
		i++;
	}
}
