/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:57:29 by thguimar          #+#    #+#             */
/*   Updated: 2025/06/09 22:50:02 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

void	free_dptr(char **dptr, int i)
{

	if (!dptr)
		return ;
	while (dptr[i])
		free(dptr[i++]);
	free(dptr);
}

void	ft_free(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

void	final_cleaner(t_shell *utils)
{
	if (utils->builtins)
		free(utils->builtins);
	if (utils->exp)
		free_dptr(utils->exp, 0);
	if (utils->command)
		free_dptr(utils->command, 0);
	if (utils->envr)
		free_dptr(utils->envr, 0);
	if (utils->export)
		free(utils->export);
	if (utils->input)
		free(utils->input);
	if (utils->echo_breed)
		free(utils->echo_breed);
	if (utils->splitex)
		free(utils->splitex);
	if (utils->right_path)
		free_dptr(utils->right_path, 0);
	if (utils)
		free(utils);
}

void	clear_little_things(t_shell *utils)
{
	final_cleaner(utils);
	exit (0);
}

void	build_exit(char **argv, t_shell *utils)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	if (!argv[1])
		clear_little_things(utils);
	else if (!argv[2])
	{
		while (ft_isdigit(argv[1][i]) == 1)
			i++;
		if (argv[1][i] != '\0')
		{
			final_cleaner(utils);
			exit (2);
		}
		else
		{
			status = ft_atoi(argv[1]);
			final_cleaner(utils);
			ft_putendl_fd("exit", 1);
			exit (status);
		}
	}
}
