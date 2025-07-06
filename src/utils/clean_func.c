/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:48:20 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/05 20:52:03 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	free_cmdr(t_cmd_r *list)
{
	t_cmd_r		*tmp;
	int			i;

	while (list)
	{
		tmp = list->next;
		if (list->args)
		{
			i = 0;
			while (list->args[i])
			{
				free(list->args[i]);
				i++;
			}
			free(list->args);
		}
		free(list);
		list = tmp;
	}
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	if (split)
		free(split);
}

void	final_cleaner(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmd)
		free_cmds(shell->cmd);
	if (shell->env)
		free_split(shell->env);
	if (shell->exp)
		free_split(shell->exp);
	if (shell->cmd_ready)
		free_cmdr(shell->cmd_ready);
	free_token_list(shell);
	free(shell);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = NULL;
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*special_cleaner(const char *s1, const char *s2, t_shell *shell)
{
	char		*tmp;

	tmp = NULL;
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	shell->list->listc = tmp;
	shell->list = shell->list->next;
	return (tmp);
}
