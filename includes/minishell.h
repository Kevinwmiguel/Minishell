/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 15:15:20 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "utils.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>


// // typedef struct s_expansion
// // {
// // 	int		i;
// // 	int		j;
// // 	int		k;
// // 	int		l;
// // 	int		x;
// // 	int		dollar;
// // 	char	**split;
// // 	char	*oq1;
// // 	char	*oq2;
// // 	char	*oq3;
// // 	char	*oq4;
// // 	char	*oq5;
// // 	char	*output;
// // 	char	*pid_str;
// // }	t_exp;

// typedef struct s_pipexinfo
// {
// 	int		fd[2];
// 	int		fd_in;
// 	int		i;
// 	int		pipe_counts;
// 	pid_t	pid;
// }	t_pipexinfo;

// typedef struct s_fdinfo
// {
// 	int	fd_in;
// 	int	fd_read;
// 	int	fd_write;
// 	int	i;
// 	int	pipe_count;
// }	t_fdinfo;
typedef struct s_red
{
	char		args[2];
	struct s_red *next;
}		t_red;


typedef struct s_cmd
{
	char	**args;
	t_red	*redirect;
	struct s_cmd *next;
}		t_cmd;


typedef struct s_shell
{
	char			**env;
	t_cmd 			*cmd; 
}		t_shell;


void print_cmd(t_cmd *cmd);

#endif