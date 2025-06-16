/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:37:48 by jmehmy            #+#    #+#             */
/*   Updated: 2025/06/16 11:23:01 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_red *redir)
{
	t_red	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->args);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd(t_cmd **cmds)
{
	t_cmd	*tmp;
	int		i;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = (*cmds)->next;
		i = 0;
		if ((*cmds)->args)
		{
			while ((*cmds)->args[i])
				free((*cmds)->args[i++]);
			free((*cmds)->args);
		}
		free_redirections((*cmds)->redirect);
		free(*cmds);
		*cmds = tmp;
	}
}

void free_str(char **str)
{
	int i;

	i = 0;
	if (!str)
		return;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

