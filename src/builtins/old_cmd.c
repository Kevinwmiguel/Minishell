/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:29:42 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/13 18:42:52 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	free_old_var(char **arr, const char *var_name)
{
	int i;
	size_t len;

	if (!arr || !var_name)
		return;
	len = ft_strlen(var_name);
	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], var_name, len) == 0 && arr[i][len] == '=')
		{
			free(arr[i]);
			arr[i] = NULL; // opcional: limpar ponteiro para evitar uso indevido
			// Se quiser, pode mover as strings subsequentes para manter arr contínuo,
			// mas depende da sua implementação
			return;
		}
		i++;
	}
}

void	update_dollar_underscore(t_shell *shell)
{
	t_cmd	*last;
	char	*full;
	char	*tmp;

	last = shell->cmd;
	while (last && last->next)
		last = last->next;
	if (last && last->args && last->args[0])
	{
		full = get_path(last->args[0], shell->env);
		if (full)
		{
			tmp = ft_strjoin("_=", full);
			if (tmp)
			{
				free_old_var(shell->env, "_");
				free_old_var(shell->exp, "_");
				shell->env = add_or_replace_env(shell->env, tmp);
				shell->exp = add_or_replace_exp(shell->exp, tmp);
				free(tmp);
			}
			free(full);
		}
	}
}
