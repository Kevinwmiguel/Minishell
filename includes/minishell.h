/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/16 11:23:15 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "utils.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7
# define DOLLAR 8


typedef struct s_signal
{
	bool			heredoc;
	pid_t			pid;
}					t_signal;

extern t_signal g_signal;

typedef struct s_red
{
	char			*args;
	int				type;
	struct s_red	*next;
}					t_red;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*line;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**args;
	t_red			*redirect;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	t_token			*begin;
	t_signal		signal;
	char			**env;
	bool			end;
	int				exit_code;
	t_cmd			*cmd;
}					t_shell;

int					process_shell_input(t_shell *data, char *str);
t_cmd				*parse_cmd(t_shell *data, t_token *token);

t_cmd				*create_cmd(t_shell *data, t_token *token);
void				add_cmd(t_cmd **list_cmd, t_cmd *new_cmd);
char				**get_cmd(t_token *token);
void				get_redirection(t_cmd *cmd, t_token *token);

bool				create_token_list(t_shell *data, char *str);
void				free_token_list(t_shell *data);
void				get_token_string(t_token *token, char **line);
void				get_type(t_token *token);
bool				handle_quote_char(char c, bool *is_single_quote,
						bool *is_double_quote);

void				join_expand(t_shell *data, char **result, char **str,
						bool is_double_quote);
char				*expand_str(t_shell *data, char *str);
char				*my_get_env(t_shell *data, char *var_name);
void				add_char(char **str, char c);
int					verify_closed_quote(char *str);

bool				special_char(char *str);
bool				is_space(char c);
void				skip_space(char **line);
char				*get_special_char(char **str);

void				handle_sigint(int code);
void				handle_sigsegv(int code);
void				handle_sigabrt(int code);

void				free_cmd(t_cmd **cmd);
void				free_redirections(t_red *redir);
void 				free_str(char **str);

void				print_cmd(t_cmd *cmd);
void				print_redirects(t_red *red);
void				debug_tokens(t_token *token);

int exec_builtin(t_cmd *cmd, t_shell *shell);
bool is_builtin(char *cmd);
int built_pwd(void);
int built_env (char **env);
int	built_cd(char **args);
int built_env (char **env);
int built_pwd(void);
int	built_cd(char **args);

#endif
