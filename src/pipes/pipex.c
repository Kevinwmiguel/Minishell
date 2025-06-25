/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:36:09 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/26 00:23:23 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

void	fixing_cmd_red(t_cmd *cmd)
{
	handle_redirection_left_input(cmd);
	handle_redirection_right_input(cmd);
}

int	find_input_file_index(char **content, int i)
{
	while (content[i])
	{
		printf("content atual %s \n ", content[1]);
		if (ft_strncmp(content[i], "<", 1) == 0)
		{
			if (content[i + 1])
				return (i + 1);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

void	remove_last_redir_pair(t_cmd *cmd, int index)
{
	int	j;

	j = index;
	while (cmd->args[j + 2])
	{
		cmd->args[j] = cmd->args[j + 2];
		j++;
	}
	cmd->args[j] = NULL;
	cmd->args[j + 1] = NULL;
}

void	remove_redir_pair(t_cmd *cmd, int index)
{
	int	j;

	j = index;
	while (cmd->args[j + 2])
	{
		cmd->args[j] = cmd->args[j + 2];
		j++;
	}
	cmd->args[j] = NULL;
	cmd->args[j + 1] = NULL;
}

void	create_empty_output_file(char *type, char *filename)
{
	int	fd;

	if (ft_strncmp(type, ">>", 2) == 0)
		fd = open(filename, O_WRONLY | O_CREAT, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	close(fd);
}

int	find_next_double_left_index(t_cmd *cmd, int start)
{
	int	i;

	i = start;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "<<", 3) == 0 && \
			ft_strlen(cmd->args[i]) == 2)
			return (i);
		i++;
	}
	return (-1);
}

void	remove_all_output_redirs(t_cmd *cmd, int last_index)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if ((i != last_index) && \
			(ft_strncmp(cmd->args[i], ">", 2) == 0 || \
			ft_strncmp(cmd->args[i], ">>", 3) == 0) && \
				cmd->args[i + 1])
		{
			create_empty_output_file(cmd->args[i], cmd->args[i + 1]);
			remove_redir_pair(cmd, i);
			continue ;
		}
		i++;
	}
	remove_last_redir_pair(cmd, last_index);
}

int	find_double_right_index(t_cmd *cmd)
{
	int			i;
	t_cmd	*temp;

	temp = cmd;
	if (!temp->args)
		return (-1);
	i = 0;
	while (temp->args[i])
	{
		i++;
		if (ft_strncmp(temp->args[i], ">>", 2) == 0 && \
			ft_strlen(temp->args[i]) == 2)
			return (i);
	}
	return (-1);
}

void	open_last_output_file(t_cmd *cmd, \
	int last_index, char *redir_type)
{
	if (ft_strncmp(redir_type, ">>", 2) == 0)
	{
		cmd->redirect->outfd = open(cmd->args[last_index + 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		cmd->redirect->outfd = open(cmd->args[last_index + 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (cmd->redirect->outfd < 0)
	{
		perror("open");
		exit(1);
	}
}

void	find_last_output_redir(t_cmd *cmd, \
	int *last_index, char **redir_type)
{
	int	i;

	i = 0;
	*last_index = -1;
	*redir_type = NULL;
	while (cmd->args[i])
	{
		if ((ft_strncmp(cmd->args[i], ">", 2) == 0 || \
			ft_strncmp(cmd->args[i], ">>", 3) == 0) && \
			cmd->args[i + 1])
		{
			*last_index = i;
			*redir_type = cmd->args[i];
		}
		i++;
	}
}

void	handle_redirection_right_input(t_cmd *cmd)
{
	int		last_index;
	char	*redir_type;

	if (!cmd || !cmd->args)
		return ;
	find_last_output_redir(cmd, &last_index, &redir_type);
	if (last_index == -1)
		return ;
	open_last_output_file(cmd, last_index, redir_type);
	remove_all_output_redirs(cmd, last_index);
}

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
	// if (!cmd || cmd->args)
	// 	return ;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "<<", 3) == 0)
		{
			cmd->redirect->heredoc = 0;
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

// char	*checker_path(t_shell *shell, char **paths, char *tmp)
// {
// 	char	*fullpath;
// 	int		i;

// 	i = 0;
// 	fullpath = NULL;
// 	if (shell->cmd->args[0][0] == '.' || shell->cmd->args[0][0] == '/')
// 	{
// 		if (access(shell->cmd->args[0], X_OK) == 0)
// 			return (ft_strdup(shell->cmd->args[0]));
// 		else
// 			return (NULL);
// 	}
// 	while (paths && paths[i])
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		fullpath = ft_strjoin(tmp, shell->cmd->args[0]);
// 		free(tmp);
// 		if (access(fullpath, X_OK) == 0)
// 			break ;
// 		free(fullpath);
// 		fullpath = NULL;
// 		i++;
// 	}
// 	return (fullpath);
// }
