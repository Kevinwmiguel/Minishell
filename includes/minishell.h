/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 15:32:25 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

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

typedef enum e_signal_type
{
	ROOT,
	CHILD,
	HEREDOC,
	IGNORE
}	t_sig_t;

typedef struct s_pipesort
{
	int	outfd; //output file
	int	infd; // input file
	int	heredoc; //here_doc file :) I hate that
}	t_pipesort;

typedef struct s_red
{
	char				args[2]; // Ex: ">", ">>", "<"
	t_pipesort			*pipe; //structure of pipes... I dont know if I trully will need that
	struct s_red		*next; // to multi redirections
}	t_red;


typedef struct s_cmd
{
	char			**args; // Array strings: ["ls", "-l", NULL]
	t_red			*redirect; // pointer to redirect list
	struct s_cmd	*next; // next cmd (pipe: `ls | wc`)
}	t_cmd;


typedef struct s_shell
{
	char	**env; // Var to env
	char	**exp; // Var to exp
	int		count;
	int		is_child;
	t_cmd	*cmd; // cmds list to be execute
}	t_shell;


void	print_cmd(t_cmd *cmd);

#endif