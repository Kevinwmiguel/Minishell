/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:39:41 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 02:38:54 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/builtins.h"

void	free_pipesort(t_pipesort *head)
{
	t_pipesort	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->content)
			free_dptr(head->content);
		free(head);
		head = tmp;
	}
}

void	strip_input_quotes(t_shell *utils)
{
	char	*clean;

	clean = remove_quotes(utils->input);
	free(utils->input);
	utils->input = clean;
}

void	main2(t_shell *utils)
{
	t_pipesort	*piped;

	while (1)
	{
		piped = ft_calloc(1, sizeof(t_pipesort));
		utils->pipe_bridge = piped;
		utils->index = 0;
		signal_search(ROOT);
		index_reset(utils);
		utils->input = readline("panic_shell>");
		if (!utils->input)
		{
			free(piped);
			break ;
		}
		add_history(utils->input);
		helper_lines2(piped, utils);
		free_pipesort(piped);
	}
}

void	utils_init(t_shell *utils, char **env)
{
	utils->export = ft_calloc(1, sizeof(t_builtvars));
	utils->j = 0;
	utils->envr = dptr_dup(env);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*utils;
	int		i;
	int		n;
	char	*num;

	i = 0;
	utils = ft_calloc(1, sizeof(t_shell));
	utils_init(utils, env);
	while (utils->envr[i] && ft_strncmp("SHLVL", utils->envr[i], \
			ft_strlen3(utils->envr[i])) != 0)
		i++;
	if (utils->envr[i] != NULL)
	{
		n = ft_atoi(utils->envr[i] + ft_strlen3(utils->envr[i]) + 1);
		n++;
		free (utils->envr[i]);
		num = ft_itoa(n);
		utils->envr[i] = ft_strjoin("SHLVL=", num);
		free (num);
	}
	else
		utils->envr[i] = ft_strdup("SHLVL=1");
	helper_lines(argc, argv, utils);
	final_cleaner(utils);
	return (0);
}
