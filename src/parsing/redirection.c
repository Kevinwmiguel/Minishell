/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-14 16:05:09 by jmehmy            #+#    #+#             */
/*   Updated: 2025-06-14 16:05:09 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	add_redirect_node(t_red **head, t_red **last, t_token *token)
{
	t_red	*redir;

	redir = malloc(sizeof(t_red));
	if (!redir)
		return (false);
	redir->type = token->type;
	redir->next = NULL;
	if (token->next)
		redir->args = ft_strdup(token->next->str);
	else
		redir->args = NULL;
	if (!redir->args)
	{
		free(redir);
		return (false);
	}
	if (!*head)
		*head = redir;
	else
		(*last)->next = redir;
	*last = redir;
	return (true);
}

void	get_redirection(t_cmd *cmd, t_token *token)
{
	t_red	*red_head;
	t_red	*last_red;

	red_head = NULL;
	last_red = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == TRUNC || token->type == APPEND
			|| token->type == INPUT || token->type == HEREDOC)
		{
			if (!add_redirect_node(&red_head, &last_red, token))
				return ;
			token = token->next;
		}
		token = token->next;
	}
	cmd->redirect = red_head;
}
