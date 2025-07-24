/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:13:23 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 13:53:37 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	remove_all_output_redirs(t_cmd *cmd, int *last_index, char **last_type)
{
	int	i;

	i = 0;
	*last_index = -1;
	*last_type = NULL;
	while (cmd->args[i])
	{
		if ((ft_strncmp(cmd->args[i], ">", 2) == 0 || ft_strncmp(cmd->args[i],
					">>", 3) == 0) && cmd->args[i + 1])
		{
			create_empty_output_file(cmd->args[i], cmd->args[i + 2]);
			*last_index = i;
			*last_type = cmd->args[i];
		}
		i++;
	}
}

int	is_last_redirection(t_cmd *cmd, char *filename)
{
	t_cmd	*tmp;
	int		i;
	size_t	len;

	len = ft_strlen(filename);
	tmp = cmd->next;
	while (tmp)
	{
		i = 1;
		while (tmp->args && tmp->args[i])
		{
			if ((ft_strncmp(tmp->args[i], ">>", 3) == 0
					|| ft_strncmp(tmp->args[i], ">", 2) == 0) && tmp->args[i
					+ 1] && ft_strncmp(tmp->args[i + 1], filename, len) == 0
				&& ft_strlen(tmp->args[i + 1]) == len)
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	is_output_redirection(char *s)
{
	return (ft_strncmp(s, ">", 2) == 0 || ft_strncmp(s, ">>", 3) == 0);
}

int	open_redir_file(char *file, char *type)
{
	if (ft_strncmp(type, ">>", 3) == 0)
		return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

void	handle_redirection_right_input(t_cmd *cmd, t_shell *shell)
{
	int		last_index;
	char	*redir_type;
	char	*outfile;

	find_last_output_redir(cmd, &last_index, &redir_type);
	if (last_index == -1)
		return ;
	outfile = cmd->args[last_index + 1];
	if (is_last_redirection(cmd, outfile))
		open_last_output_file(cmd, last_index, redir_type, shell);
	else
		cmd->redirect->outfd = -2;
}
