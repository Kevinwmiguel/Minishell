/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder_and_comm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:03:59 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/18 19:04:38 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	l_comander(t_shell *shell, char *args)
{
	if (is_valid_identifier(args))
	{
		if (ft_strchr(args, '='))
			update_env_var(shell, args);
		else
			update_export_var(shell, args);
	}
	else
		ft_putstr_fd("export: not a valid identifier\n", 2);
}

void	finder_and_update(t_shell *shell)
{
	t_cmd	*head;
	char	*full;
	char	*tmp;

	full = NULL;
	head = shell->cmd;
	while (head->next)
		head = head->next;
	full = get_path(head->args[0], shell->env);
	tmp = ft_strjoin("_=", full);
	free(full);
	l_comander(shell, tmp);
	free (tmp);
}

int	check_is_dir(const char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}
