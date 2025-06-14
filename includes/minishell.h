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

typedef struct s_signal
{
	bool heredoc;
	pid_t pid;
} t_signal;

extern t_signal g_signal;

typedef struct s_red
{
	char		*args;
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
} t_cmd;

typedef struct s_shell
{
	t_token *begin;
	t_env *env_list;
	t_signal signal;
	char			**env;
	char **test;
	bool end;
	int				exit_code;
	t_cmd 	*cmd;
} t_shell;

void print_cmd(t_cmd *cmd);
void print_redirects(t_red *red);
void debug_tokens(t_token *token);

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

bool create_token_list(t_shell *data, char *str);
void free_token_list(t_shell *data);
void get_token_string(t_token *token, char **line);
void get_type(t_token *token);
bool handle_quote_char (char c, bool *is_single_quote, bool *is_double_quote);
void add_cmd(t_cmd **list_cmd, t_cmd *new_cmd);
t_cmd *create_cmd(t_shell *data, t_token *token);

char **get_cmd(t_token *token);
void free_cmd(t_cmd **cmd);
bool special_char( char *str);
bool is_space(char c);
void skip_space(char **line);
char *get_special_char(char **str);
void get_redirection(t_cmd *cmd, t_token *token);
void free_redirections(t_red *redir);


#endif
