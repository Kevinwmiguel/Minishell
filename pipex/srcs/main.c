/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:54:34 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/09 22:49:55 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/builtins.h"

int	pipex_start(t_pipesort *piped, t_shell *utils)
{
	while (utils->command[utils->j])
		utils->j++;
	path_comms(piped->content, utils, piped);
	utils->j = 0;
	//LIMPEZA AQUI
	return (0);
}

void	pipex(int argc, t_pipesort *piped, t_shell *utils, char *path)
{
	t_files		*file;
	t_pipesort	*head;

	piped->outfd = 0;
	file = malloc(sizeof(t_files));
	init_func(file, utils->envr, piped, argc);
	file->paths = path;
	head = piped;
	while (piped->content)
	{
		handle_redirection_left_input(piped);
		handle_redirection_right_input(piped);
		piped = piped->next;
	}
	piped = head;
	main3pipex(file, piped, utils);
	free(head);
	free(file);
}
