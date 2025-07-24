/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:23:06 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/24 13:56:53 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*get_pwd_var(void)
{
	char	cwd[4096];
	char	*res;

	res = NULL;
	if (getcwd(cwd, sizeof(cwd)))
		res = ft_strjoin("PWD=", cwd);
	else
		res = ft_strdup("PWD=");
	return (res);
}

char	*get_path_var(char *home)
{
	char	*res;
	char	*local;
	char	*base;

	res = NULL;
	if (home)
	{
		local = ft_strjoin(home, "/.local/bin");
		base = ft_strjoin("PATH=/usr/local/sbin:/usr/local/bin:"
				"/usr/sbin:/usr/bin:/sbin:/bin:", local);
		free(local);
		res = base;
	}
	else
	{
		res = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:"
				"/usr/sbin:/usr/bin:/sbin:/bin");
	}
	return (res);
}

void	truncate_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
		close(fd);
}
