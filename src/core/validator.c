/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:34:28 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/25 01:42:05 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	is_valid_input(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] == '>' || str[i - 1] == '<')
		return (1);
	return (0);
}

void	validator(char *input, t_shell *shell)
{
	shell->mistake = is_valid_input(input);
	if (shell->mistake)
	{
		free(input);
		return ;
	}
	add_history(input);
	if (ft_strlen(input) != 0 && process_shell_input(shell, input))
	{
		shell->cmd = parse_cmd(shell, shell->begin);
		exec_clean(shell);
	}
}
