/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:49:27 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/17 19:19:42 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

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

void	update_env_var(t_shell *shell, char *arg)
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

void	update_export_var(t_shell *shell, char *arg)
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
			{
				if (check_duplicate_var_exist(shell->exp, arg) == 0)
					update_export_var(shell, arg);
			}
		}
		else
			ft_putstr_fd("export: not a valid identifier\n", 2);
		i++;
	}
}
