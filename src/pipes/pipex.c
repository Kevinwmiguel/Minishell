/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:36:09 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/17 22:19:47 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// pid_t pid;

// pid = fork();
// if (pid == 0)
// {
// 	shell->is_child = 1; // Estamos no filho
// 	// Executa o comando (incluindo build_exit, se for o caso)
// }
// else
// {
// 	shell->is_child = 0; // Pai continua
// 	waitpid(pid, NULL, 0); // Aguarda o filho
// }

int	find_double_right_index(t_pipesort *piped)
{
	int			i;
	t_pipesort	*temp;

	temp = piped;
	if (!temp->content)
		return (-1);
	i = 0;
	while (temp->content[i])
	{
		i++;
		if (ft_strncmp(temp->content[i], ">>", 2) == 0 && \
			ft_strlen(temp->content[i]) == 2)
			return (i);
	}
	return (-1);
}

void	open_last_output_file(t_pipesort *piped, \
	int last_index, char *redir_type)
{
	if (ft_strncmp(redir_type, ">>", 2) == 0)
	{
		piped->outfd = open(piped->content[last_index + 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		piped->outfd = open(piped->content[last_index + 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (piped->outfd < 0)
	{
		perror("open");
		exit(1);
	}
}

void	find_last_output_redir(t_pipesort *piped, \
	int *last_index, char **redir_type)
{
	int	i;

	i = 0;
	*last_index = -1;
	*redir_type = NULL;
	while (piped->content[i])
	{
		if ((ft_strncmp(piped->content[i], ">", 2) == 0 || \
			ft_strncmp(piped->content[i], ">>", 3) == 0) && \
			piped->content[i + 1])
		{
			*last_index = i;
			*redir_type = piped->content[i];
		}
		i++;
	}
}

void	handle_redirection_right_input(t_pipesort *piped)
{
	int		last_index;
	char	*redir_type;

	if (!piped || !piped->content)
		return ;
	find_last_output_redir(piped, &last_index, &redir_type);
	if (last_index == -1)
		return ;
	open_last_output_file(piped, last_index, redir_type);
	remove_all_output_redirs(piped, last_index);
}

void	remove_all_double_left_tokens(t_pipesort *piped)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (piped->content[i])
	{
		if (ft_strncmp(piped->content[i], "<<", 3) == 0)
		{
			j = i;
			while (piped->content[j + 2])
			{
				piped->content[j] = piped->content[j + 2];
				j++;
			}
			piped->content[j] = NULL;
			piped->content[j + 1] = NULL;
			continue ;
		}
		i++;
		k++;
	}
}

void	remove_one_left_tokens(t_pipesort *piped, int file_idx)
{
	int	i;

	i = file_idx - 1;
	while (piped->content[i + 1])
	{
		piped->content[i] = piped->content[i + 1];
		i++;
	}
	piped->content[i] = NULL;
}

void	handle_double_left(t_pipesort *piped)
{
	int	idx;
	int	idx_limiter;

	idx = 0;
	while ((find_next_double_left_index(piped, idx)) != -1)
	{
		idx = find_next_double_left_index(piped, idx);
		idx_limiter = idx + 1;
		if (!piped->content[idx_limiter])
		{
			write(2, "Limite ausente para heredoc\n", 29);
			exit(1);
		}
		piped->heredoc_fd = here_doc(piped->content[idx_limiter]);
		idx = idx_limiter;
	}
	remove_all_double_left_tokens(piped);
}

void	handle_single_left(t_pipesort *piped)
{
	int	file_index;

	file_index = find_input_file_index(piped->content, 0);
	if (file_index == -1)
	{
		write(2, "Arquivo não fornecido para redirecionamento\n", 45);
		exit(1);
	}
	piped->infd = open(piped->content[file_index], O_RDONLY);
	if (piped->infd < 0)
	{
		perror("open");
		exit(1);
	}
	remove_one_left_tokens(piped, file_index);
}

void	handle_redirection_left_input(t_pipesort *piped)
{
	int	i;

	i = 0;
	if (!piped || !piped->content || !piped->redirection_type)
		return ;
	while (piped->content[i])
	{
		if (ft_strncmp(piped->content[i], "<<", 3) == 0)
		{
			handle_double_left(piped);
			i = 0;
			continue ;
		}
		else if (ft_strncmp(piped->content[i], "<", 2) == 0)
		{
			handle_single_left(piped);
			i = 0;
			continue ;
		}
		i++;
	}
}

char	*checker_path(t_shell *shell, char **paths, char *tmp)
{
	char	*fullpath;
	int		i;

	i = 0;
	fullpath = NULL;
	if (shell->cmd->args[0][0] == '.' || shell->cmd->args[0][0] == '/')
	{
		if (access(shell->cmd->args[0], X_OK) == 0)
			return (ft_strdup(shell->cmd->args[0]));
		else
			return (NULL);
	}
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpath = ft_strjoin(tmp, shell->cmd->args[0]);
		free(tmp);
		if (access(fullpath, X_OK) == 0)
			break ;
		free(fullpath);
		fullpath = NULL;
		i++;
	}
	return (fullpath);
}
