/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:02:10 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 13:32:16 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_cmd_r	*alloc_clean_cmd_list(t_cmd *cmd)
{
	t_cmd_r	*head;
	t_cmd_r	*curr;
	t_cmd_r	*new;

	head = NULL;
	curr = NULL;
	while (cmd)
	{
		new = malloc(sizeof(t_cmd_r));
		if (!new)
			return (NULL);
		new->args = NULL;
		new->next = NULL;
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		cmd = cmd->next;
	}
	return (head);
}

int	has_heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strncmp(cmd->args[0], "<<", 3) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	fill_clean_args(t_cmd *cmd, t_cmd_r *clean)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (is_redirection_token(cmd->args[i]) && cmd->args[i + 1])
		{
			if (!ft_strncmp(cmd->args[0], "ls", 3) && !ft_strncmp(cmd->args[i],
					"<", 2))
				clean->args[j++] = ft_strdup(cmd->args[i + 1]);
			i += 2;
		}
		else
			clean->args[j++] = ft_strdup(cmd->args[i++]);
	}
	clean->args[j] = NULL;
}

int	count_clean_args(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->args[i])
	{
		if (is_redirection_token(cmd->args[i]) && cmd->args[i + 1])
		{
			if (!ft_strncmp(cmd->args[0], "ls", 3) && !ft_strncmp(cmd->args[i],
					"<", 2))
				count++;
			i += 2;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	import_args_to_clean(t_cmd *cmd, t_cmd_r *clean)
{
	int	count;

	if (!cmd || !cmd->args || !clean)
		return ;
	count = count_clean_args(cmd);
	if (count == 0 && has_heredoc(cmd))
	{
		cmd->skip = 1;
		clean->args = malloc(sizeof(char *) * 2);
		if (!clean->args)
			return ;
		clean->args[0] = ft_strdup("cat");
		clean->args[1] = NULL;
		return ;
	}
	clean->args = malloc(sizeof(char *) * (count + 1));
	if (!clean->args)
		return ;
	fill_clean_args(cmd, clean);
}
