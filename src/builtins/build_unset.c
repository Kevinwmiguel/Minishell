/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:36:45 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/10 12:38:46 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

int	should_skip(char *env_entry, char **args)
{
	int		i;
	int		len;

	i = 1;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		if (ft_strncmp(env_entry, args[i], len) == 0
			&& env_entry[len] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**copy_env_without_vars(char **old_env, char **args)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = ft_calloc(mlc_size(0, old_env) + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	j = 0;
	while (old_env[++i])
	{
		if (!should_skip(old_env[i], args))
			new_env[j++] = ft_strdup(old_env[i]);
	}
	new_env[j] = NULL;
	return (new_env);
}

int	var_not_found(char **env, char **args)
{
	int	i;
	int	j;
	int	len;

	j = 1;
	while (args[j])
	{
		i = 0;
		len = ft_strlen(args[j]);
		while (env[i])
		{
			if (ft_strncmp(env[i], args[j], len) == 0 && env[i][len] == '=')
				break ;
			i++;
		}
		if (!env[i])
			return (1);
		j++;
	}
	return (0);
}

void	build_unset(t_shell *shell)
{
	char	**new_env;
	char	**new_exp;
	char	**merged;

	if (!shell->cmd || !shell->cmd->args[1])
		return ;
	if (var_not_found(shell->env, shell->cmd->args))
	{
		write(2, "unset: variable does not exist\n", 32);
		//final_cleaner(shell);
		close_extra_fds();
		return ;
	}
	new_env = copy_env_without_vars(shell->env, shell->cmd->args);
	if (!new_env)
		return ;
	free_env(shell->env);
	shell->env = new_env;
	new_exp = build_export(shell);
	if (!new_exp)
		return ;
	merged = merge_exp_lists(shell->exp, new_exp, shell->env);
	free_dptr(new_exp);
	if (!merged)
		return ;
	free_dptr(shell->exp);
	shell->exp = merged;
}
