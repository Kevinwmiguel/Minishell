/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:49:27 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/03 13:10:05 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	find_in_env(char **env, const char *key)
{
	int		i;
	int		len;
	char	*equal;

	i = 0;
	len = ft_strlen(key);
	while (env && env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal && (int)(equal - env[i]) == len)
		{
			if (ft_strncmp(env[i], key, len) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

// static char	**merge_exp_lists(char **old_exp, char **new_exp, char **env)
// {
// 	int		i;
// 	char	**merged;
// 	int		count;

// 	i = 0;
// 	count = mlc_size(0, old_exp) + mlc_size(0, new_exp);
// 	merged = ft_calloc(count + 1, sizeof(char *));
// 	if (!merged)
// 		return (NULL);
// 	count = 0;
// 	while (new_exp && new_exp[i])
// 	{
// 		merged[count] = ft_strdup(new_exp[i]);
// 		if (!merged[count])
// 			return (free_split(merged), NULL);
// 		count++;
// 		i++;
// 	}
// 	i = 0;
// 	while (old_exp && old_exp[i])
// 	{
// 		if (!ft_strchr(old_exp[i], '=') && !find_in_env(env, old_exp[i]))
// 		{
// 			merged[count] = ft_strdup(old_exp[i]);
// 			if (!merged[count])
// 				return (free_split(merged), NULL);
// 			count++;
// 		}
// 		i++;
// 	}
// 	merged[count] = NULL;
// 	return (merged);
// }

static void	update_env_var(t_shell *shell, char *arg)
{
	char	**tmp;
	char	**new_exp;

	tmp = add_or_replace_env(shell->env, arg);
	if (!tmp)
		return ;
	free_dptr(shell->env);
	shell->env = tmp;
	new_exp = build_export(shell);
	if (!new_exp)
		return ;
	tmp = merge_exp_lists(shell->exp, new_exp, shell->env);
	free_dptr(new_exp);
	if (!tmp)
		return ;
	free_dptr(shell->exp);
	shell->exp = tmp;
}

static void	update_export_var(t_shell *shell, char *arg)
{
	char	**tmp;

	tmp = add_or_replace_exp(shell->exp, arg);
	if (!tmp)
		return ;
	free_dptr(shell->exp);
	shell->exp = tmp;
}

void	update_env_export(t_shell *shell, char **args)
{
	int		i;
	char	*arg;

	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (is_valid_identifier(arg))
		{
			if (ft_strchr(arg, '='))
				update_env_var(shell, arg);
			else
				update_export_var(shell, arg);
		}
		else
			ft_putstr_fd("export: not a valid identifier\n", 2);
		i++;
	}
}
