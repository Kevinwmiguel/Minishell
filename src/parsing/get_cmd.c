/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:12:43 by jmehmy            #+#    #+#             */
/*   Updated: 2025/06/17 11:52:45 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmd_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE && token->type != INPUT
		&& token->type != HEREDOC && token->type != TRUNC
		&& token->type != APPEND)
	{
		if (token->type == CMD || token->type == ARG)
			count++;
		token = token->next;
	}
	return (count);
}

static void	fill_cmd_args(char **cmd_args, t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE && token->type != INPUT
		&& token->type != HEREDOC && token->type != TRUNC
		&& token->type != APPEND)
	{
		if (token->type == CMD || token->type == ARG)
			cmd_args[i++] = ft_strdup(token->str);
		token = token->next;
	}
	cmd_args[i] = NULL;
}

char	**get_cmd(t_token *token)
{
	int		count;
	char	**cmd_args;

	count = count_cmd_args(token);
	cmd_args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_args)
		return (NULL);
	fill_cmd_args(cmd_args, token);
	return (cmd_args);
}
