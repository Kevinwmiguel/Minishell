/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:38:08 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 14:02:46 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

void	helper_lines2(t_pipesort *piped, t_shell *utils)
{
	if (quotes_verify(utils->input) == 0)
	{
		strip_input_quotes(utils);
		if (pipe_verify(utils->input, 0) == 0)
		{
			utils->count_hp = 0;
			utils->command = pipping_commands(utils->input);
			if (scary_thing(piped, utils) == 1)
				pipex_start(piped, utils);
			free_dptr(utils->command);
			free(utils->input);
		}
	}
}

void	helper_lines(int argc, char **argv, t_shell *utils)
{
	char	**temp;

	temp = bubble_sort(0, utils->envr, 0, argc);
	utils->exp = temp;
	if (argc != 1 || argv[1])
	{
		printf("invalid args (no args should be used)\n");
		//limpeza
		exit (1);
	}
	main2(utils);
}
