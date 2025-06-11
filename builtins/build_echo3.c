/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 02:44:14 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 02:46:20 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

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
