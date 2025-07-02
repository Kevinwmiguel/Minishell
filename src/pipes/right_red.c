/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:13:23 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/02 00:01:44 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

// void prepare_all_output_files(t_cmd *cmd)
// {
// 	int i;

// 	i = 0;
// 	while (cmd->args[i])
// 	{
// 		if ((ft_strncmp(cmd->args[i], ">", 2) == 0 || ft_strncmp(cmd->args[i], ">>", 3) == 0)
// 			&& cmd->args[i + 1])
// 		{
// 			create_empty_output_file(cmd->args[i], cmd->args[i + 1]);
// 		}
// 		i++;
// 	}
// }

int	is_redirection_token(char *s)
{
	return (!ft_strncmp(s, ">", 2) || !ft_strncmp(s, ">>", 3)
		|| !ft_strncmp(s, "<", 2) || !ft_strncmp(s, "<<", 3));
}

void	import_args_to_clean(t_cmd *cmd, t_cmd_r *clean)
{
	int	i;
	int	j;
	int	count;

	if (!cmd || !cmd->args || !clean)
		return ;

	// 1. Conta quantos args válidos existem
	i = 0;
	count = 0;
	while (cmd->args[i])
	{
		if (is_redirection_token(cmd->args[i]) && cmd->args[i + 1])
			i += 2;
		else
		{
			count++;
			i++;
		}
	}

	// 2. Aloca espaço para clean->args
	clean->args = malloc(sizeof(char *) * (count + 1));
	if (!clean->args)
		return ;

	// 3. Copia os args válidos
	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (is_redirection_token(cmd->args[i]) && cmd->args[i + 1])
			i += 2;
		else
			clean->args[j++] = ft_strdup(cmd->args[i++]);
	}
	clean->args[j] = NULL;
}

void	remove_all_output_redirs(t_cmd *cmd, int *last_index, char **last_type)
{
	int	i;

	i = 0;
	*last_index = -1;
	*last_type = NULL;

	while (cmd->args[i])
	{
		if ((ft_strncmp(cmd->args[i], ">", 2) == 0 || ft_strncmp(cmd->args[i], ">>", 3) == 0)
			&& cmd->args[i + 1])
		{
			// Só criamos os arquivos antecipadamente, mas não mexemos em args
			create_empty_output_file(cmd->args[i], cmd->args[i + 2]);

			// Guardamos o último redir válido
			*last_index = i;
			*last_type = cmd->args[i];
		}
		i++;
	}
}

int	find_double_right_index(t_cmd *cmd)
{
	int			i;
	t_cmd		*temp;

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
	//remove_all_output_redirs(cmd, last_index, clean);
	
}

void	open_last_output_file(t_cmd *cmd, \
	int last_index, char *redir_type)
{
	if (ft_strncmp(redir_type, ">>", 3) == 0)
	{
		cmd->redirect->outfd = open(cmd->args[last_index + 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if ((ft_strncmp(redir_type, ">", 2) == 0))
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
