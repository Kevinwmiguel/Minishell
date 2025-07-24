/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:59:57 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/29 21:47:18 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	update_pwd_in(char **arr, char *new_pwd)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (!ft_strncmp(arr[i], "PWD=", 4))
		{
			free(arr[i]);
			arr[i] = ft_strdup(new_pwd);
			break ;
		}
		i++;
	}
}

void	update_pwd(t_shell *shell)
{
	char	cwd[4096];
	char	*new_pwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return ;
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return ;
	update_pwd_in(shell->env, new_pwd);
	update_pwd_in(shell->exp, new_pwd);
	free(new_pwd);
}

void	build_pwd(t_shell *shell)
{
	char	cwd[4096];

	(void)shell;
	if (getcwd(cwd, 4096))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
}
