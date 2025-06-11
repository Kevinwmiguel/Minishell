/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:19:40 by thiago-camp       #+#    #+#             */
/*   Updated: 2025/06/11 03:14:01 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"
#include "../libft/libft.h"

char	*remove_after_redir_if_last(t_shell *utils, \
	int cut_pos, int last_pipe, int i)
{
	utils->new = NULL;
	while (utils->tmp[i])
	{
		if (utils->tmp[i] == '>' && utils->tmp[i + 1] == '>')
		{
			cut_pos = i;
			i++;
		}
		else if (utils->tmp[i] == '>' || utils->tmp[i] == '<')
			cut_pos = i;
		else if (utils->tmp[i] == '|')
			last_pipe = i;
		i++;
	}
	if (cut_pos != -1 && cut_pos > last_pipe)
	{
		utils->new = malloc(cut_pos + 1);
		if (!utils->new)
			return (NULL);
		ft_strncpy(utils->new, utils->tmp, cut_pos);
		utils->new[cut_pos] = '\0';
		return (utils->new);
	}
	return (ft_strdup(utils->tmp));
}

void	process_and_print_output(char **final_reader, char *arr, t_shell *utils)
{
	char	*output;
	int		i;

	i = 0;
	output = NULL;
	utils->processed_output = NULL;
	output = double_to_one(final_reader);
	utils->tmp = remove_before_last_echo(output);
	free(output);
	utils->third = remove_after_last_cat(utils->tmp);
	free(utils->tmp);
	utils->tmp = trim_start(utils->third);
	free(utils->third);
	utils->processed_output = remove_after_redir_if_last(utils, -1, -1, 0);
	free(utils->tmp);
	ft_putstr_fd(utils->processed_output, 1);
	if (echo_flag(arr) == 0)
		ft_putstr_fd("\n", 1);
	while (final_reader && final_reader[i])
		free(final_reader[i++]);
	free(final_reader);
	free(utils->processed_output);
	utils->processed_output = NULL;
}

void	process_echo_segment(t_shell *utils)
{
	if (utils->arr[utils->i] == '"' || utils->arr[utils->i] == '\'')
		handle_quotes_echo(utils);
	else
		handle_no_quotes_echo(utils);
	utils->str = ft_substr(utils->arr, utils->i, utils->x);
	utils->y++;
	utils->final_reader[utils->y] = \
	expansions(utils->str, utils, utils->echo_pa);
	free(utils->str);
	if (utils->echo_pa > 0)
		utils->i++;
	utils->i += utils->x;
}

void	build_echo(char *arr, t_shell *utils, int i, int j)
{
	utils->arr = arr;
	utils->i = i;
	utils->y = j;
	utils->echo_pa = 0;
	utils->final_reader = ft_calloc(sizeof(char *), final_reader_size(arr) + 1);
	if (!utils->final_reader)
		return ;
	if (echo_flag(arr) == 1)
		utils->i += flag_count(arr);
	while (arr[utils->i])
		process_echo_segment(utils);
	process_and_print_output(utils->final_reader, arr, utils);
}
