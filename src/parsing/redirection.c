/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:05:09 by jmehmy            #+#    #+#             */
/*   Updated: 2025/06/29 23:12:21 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_starter(t_red *redir, t_token *token)
{
	redir->heredoc = -1;
	redir->infd = -1;
	redir->outfd = -1;
	redir->type = token->type;
	redir->next = NULL;
}

static bool	add_redirect_node(t_red **head, t_red **last, t_token *token)
{
	t_red	*redir;

	redir = malloc(sizeof(t_red));
	if (!redir)
		return (false);
	ft_bzero(redir, sizeof(t_red));
	redir_starter(redir, token);
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
