/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:19:40 by thiago-camp       #+#    #+#             */
/*   Updated: 2025/06/09 18:12:30 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"
#include "../libft/libft.h"

char *remove_after_redir_if_last(char *str)
{
	int i = 0;
	int cut_pos = -1;
	int last_pipe = -1;
	char *new;

	new = NULL;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			cut_pos = i;
			i++;
		}
		else if (str[i] == '>' || str[i] == '<')
			cut_pos = i;
		else if (str[i] == '|')
			last_pipe = i;
		i++;
	}
	if (cut_pos != -1 && cut_pos > last_pipe)
	{
		new = malloc(cut_pos + 1);
		if (!new)
			return (NULL);
		ft_strncpy(new, str, cut_pos);
		new[cut_pos] = '\0';
		return (new);
	}
	return (ft_strdup(str));
}

void	process_and_print_output(char **final_reader, char *arr, t_shell *utils)
{
	char	*output;
	char	*tmp;

	utils->processed_output = NULL;
	output = double_to_one(final_reader);
	tmp = remove_before_last_echo(output);
	utils->processed_output = trim_start(tmp);
	free(tmp);
	tmp = utils->processed_output;
	utils->processed_output = remove_after_redir_if_last(tmp);
	free(tmp);
	ft_putstr_fd(utils->processed_output, 1);
	if (echo_flag(arr) == 0)
		ft_putstr_fd("\n", 1);
	free(final_reader);
	free(output);
	free(utils->processed_output);
}

void	handle_quotes_echo(t_shell *utils)
{
	if (utils->arr[utils->i] == '"')
	{
		utils->i++;
		utils->echo_pa = 1;
		utils->x = in_between('"', utils->arr, utils->i);
	}
	else if (utils->arr[utils->i] == '\'')
	{
		utils->i++;
		utils->echo_pa = 2;
		utils->x = in_between('\'', utils->arr, utils->i);
	}
}

void	handle_no_quotes_echo(t_shell *utils)
{
	utils->echo_pa = 0;
	utils->x = 0;
	while (utils->arr[utils->i + utils->x]
		&& utils->arr[utils->i + utils->x] != '\''
		&& utils->arr[utils->i + utils->x] != '"')
		utils->x++;
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
	free_dptr(utils->final_reader, 0);
}
