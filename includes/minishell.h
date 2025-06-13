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

#ifndef MINISHELL_H
# define MINISHELL_H

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

 
#define INPUT  1
#define HEREDOC  2
#define TRUNC 3
#define APPEND 4
#define PIPE 5
#define CMD 6
#define ARG 7
#define DOLLAR 8

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
	int type;
	struct s_red *next;
}		t_red;

typedef struct s_token
{
	char *str;
	int type;
	struct s_token *prev;
	struct s_token *next;
} t_token;

typedef struct s_env
{
	char *line;
	struct s_env *prev;
	struct s_env *next;
} t_env;

typedef struct s_cmd
{
	char	**args;
	t_red	*redirect;
	struct s_cmd *next;
}		t_cmd;

typedef struct s_shell
{
	t_token *begin;
	t_env *env;
	t_signal signal;
	char			**env;
	char **test;
	struct t_cmd 			*cmd;
	bool end;
	int				exit_code;
	t_token			*begin;
}		t_shell;

typedef struct s_signal
{
	bool heredoc;
	pid_t pid;
} t_signal;


void print_cmd(t_cmd *cmd);
int		process_shell_input(t_shell *data, char *str);
t_cmd *parse_cmd(t_shell *data, t_token *token);

void join_expand(t_shell *data, char **result, char **str, bool is_double_quote);
char	*expand_str(t_shell *data, char *str);
void add_char(char **str, char c);
int verify_closed_quote(char *str);
char *my_get_env(t_shell *data, char *var_name);

void handle_sigint(int code);
void handle_sigsegv(int code);
void handle_sigabrt(int code);

bool creat_token_list(t_shell *data, char *str);
void free_token_list(t_shell *data);
void get_token_string(t_token *token, char **line);
void get_type(t_token *token);
bool handle_quote_char (char c, bool *is_single_quote, bool *is_double_quote);

#endif