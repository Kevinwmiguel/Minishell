/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:40:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/11 03:13:46 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# define PATH "/home/thguimar/bin:/usr/local/sbin:/usr/local/bin:/usr/ \
sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"

// typedef struct s_expansion
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		l;
// 	int		x;
// 	int		dollar;
// 	char	**split;
// 	char	*oq1;
// 	char	*oq2;
// 	char	*oq3;
// 	char	*oq4;
// 	char	*oq5;
// 	char	*output;
// 	char	*pid_str;
// }	t_exp;

typedef struct s_pipexinfo
{
	int		fd[2];
	int		fd_in;
	int		i;
	int		pipe_counts;
	pid_t	pid;
}	t_pipexinfo;

typedef struct s_fdinfo
{
	int	fd_in;
	int	fd_read;
	int	fd_write;
	int	i;
	int	pipe_count;
}	t_fdinfo;

typedef enum e_signal_type
{
	ROOT,
	CHILD,
	HEREDOC,
	IGNORE,
}				t_signal_type;

typedef struct s_pipesort
{
	int					id;
	int					heredoc_fd;
	int					infd;
	int					outfd;
	int					pid;
	bool				redirection;
	char				*redirection_type;
	char				*file;
	char				**content;
	int					pwd_storage;
	int					export_red;
	struct s_pipesort	*next;
	struct s_pipesort	*prev;
}		t_pipesort;

typedef struct s_builtvars
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
	int		n;
	int		x;
	int		flag;
	char	**mlc;
}		t_builtvars;

typedef struct s_builtvars2
{
	int		i;
	int		j;
	int		l;
	int		m;
	int		flag;
	int		tries;
	char	**clc;
}		t_builtvars2;

typedef struct s_shell
{
	char			**exp;
	char			**envr;
	char			**builtins;
	char			**command;
	char			*echo_breed;
	char			***bizarre;
	char			*input;
	char			*echo_buffer;
	char			**right_path;
	char			*resolved_path;
	char			*processed_output;
	int				j;
	int				index;
	int				process_id;
	int				export_j;
	t_builtvars		*export;
	t_builtvars2	*cd;
	t_pipesort		*pipe_bridge;
	char			*arr;
	int				i;
	int				y;
	int				x;
	int				echo_pa;
	int				count_hp;
	char			*str;
	char			**final_reader;
	char			*o_que_quiser;
	char			*o_que_quiser2;
	char			*o_que_quiser3;
	char			*o_que_quiser4;
	char			*o_que_quiser5;
	int				count_m;
	int				count_n;
	int				count_h;
	char			**splitex;
	char			*output_ex;
	char			dollar;
	int				count_var;
	char			*tmp;
	char			*third;
	char			*new;
}		t_shell;

typedef struct s_cd
{
	char	*user;
	int		flag;
	char	*str;
	char	*joined;
	int		i;
	int		j;
	int		x;
	t_shell	*utils;
}		t_cd;

//global char *bultins[2] = {"echo", "cd"};
//Export Functions

typedef struct datafile
{
	int		infile;
	int		outfile;
	char	**envp;
	char	***cmds;
	int		cmd_count;
	int		pipe_fd[2];
	char	*paths;
}	t_files;

void	strip_input_quotes(t_shell *utils);
void	free_triple_ptr(char ***ptr);
void	wyw_start(t_shell *utils);
char	*expand_pid(char *str, int j, t_shell *utils);
int		pid_dollar(char *str, int j);
int		varlen(char *str, int k);
int		in_between(char c, char *str, int i);
char	*expansions(char *argv, t_shell *utils, int pa);
void	free_expansion(t_shell *utils);
char	*expand_env(char *str, t_shell *utils);
int		check_infile(char *file);
int		builtin_not_command(char **argv);
int		check_accessible(const char *path);
char	*double_to_one(char **dptr);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
char	*get_directory_path(char *path);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	**add_file_to_cmd(char **cmd, char *file_path);
size_t	length2(char *cmd);
size_t	length(char **cmd);
void	final_cleaner9(t_files *file);
char	*ft_strrstr(const char *haystack, const char *needle);

// new
void	free_split(char **split);
void	close_inout(t_files *file);
char	*trim_start(char *str);

//path
void	path_cleaner(char **paths);
void	pick_path2(t_files *file, char **path, int cmd_idx, int path_idx);
char	**pick_path(char **envp);
int		pipex_start(t_pipesort *piped, t_shell *utils);
void	pipex(int argc, t_pipesort *piped, t_shell *utils, char *path);
int		is_command(const char *arg);
int		here_doc(char *limiter);
void	handle_redirection_right_input(t_pipesort *piped);
int		ft_lstsize_pipesort(t_pipesort *lst);

void	main3pipex(t_files *file, t_pipesort *piped, t_shell *utils);
void	remove_double_right_tokens(t_pipesort *piped, int limiter_idx);
int		find_double_right_index(t_pipesort *piped);
int		find_input_file_index(char **content, int i);
void	remove_double_left_tokens(t_pipesort *piped, int limiter_idx);
void	remove_one_left_tokens(t_pipesort *piped, int file_idx);
void	handle_redirection_left_input(t_pipesort *piped);
void	remove_one_right_tokens(t_pipesort *piped, int file_idx);

char	*find_command_path(char *cmd, char **envp);
char	**get_paths_from_env(char **envp);
void	exec_comm(char **cmd_args, char **envp, \
		t_pipesort *piped, t_shell *utils);
void	handle_redirection_right_input_comms(t_pipesort *piped);
int		quotes_verify(char *argv);
void	init_func(t_files *file, char **envp, t_pipesort *piped, int argc);
void	inform_path_error(void);
void	init_pipexinfo(t_pipexinfo *px, t_pipesort *piped);
int		find_next_double_left_index(t_pipesort *piped, int start);
int		find_input_file_index(char **content, int i);
int		count_heredocs(t_pipesort *piped);
void	remove_all_output_redirs(t_pipesort *piped, int last_index);
void	remove_one_right_tokens(t_pipesort *piped, int file_idx);
void	remove_double_right_tokens(t_pipesort *piped, int limiter_idx);
int		scary_thing(t_pipesort	*piped, t_shell *utils);
int		dptr_len(char **dptr);
void	helper_lines2(t_pipesort *piped, t_shell *utils);
void	main2(t_shell *utils);
int		echo_flag(char *argv);
int		flag_count(char *argv);
int		final_reader_size(char *str);
char	*remove_after_last_cat(char *str);
char	*remove_before_last_echo(char *str);

char	*remove_quotes(const char *str);
char	*malloc_no_quotes(const char *str);
void	copy_without_quotes(char *dest, const char *src);
int		count_without_quotes(const char *str, int i);

/////////////

char	**bubble_sort(int j, char **mlc, int flag, int argc);
char	**exp_copy(char **exp);
char	**exp_copy2(char **exp, int argc);
int		equal_vars(char **exp, char **argv, int j, int flag);
char	**dptr_dup(char	**dptr);
int		ft_strcmp2(char *s1, char *s2);
int		ft_strlen3(char *str);
int		is_there_equals(char *argv);
int		line_waste(t_builtvars *export, char **argv, int flag, int j);
int		mlc_size(int j, char **mlc);
int		var_equal_line(char **env, char **argv, int j);
int		write_exp2(t_shell *utils, int flag, int j, int i);
int		mlc_size(int j, char **mlc);
void	argc2(t_shell *utils, char **argv, int j, int argc);
void	export_helper(t_builtvars *export, char **argv, int j);
void	export_helper2(char **mlc, char **argv, int i);
void	export_helper_helper(t_builtvars *export, char **argv, int j);
void	export_hha(char **argv, t_builtvars *export, int j, int flag);
char	**remove_redirection(char **cmd, int index);
void	index_reset(t_shell *utils);
void	write_exp(t_shell *utils);

//Unset Functions

int		ft_strlen4(char *str);
int		there_is_an_equal_argv(char **argv, char *env);
int		unset_argv_checker(char *exp, char **argv);
int		unset_flag(int flag, char *exp, char *argv);
int		var_comp2(char **env, char **argv, int j);
int		var_equal_line2(char **env, char *argv);
void	write_env(int j, char **mlc);

//ECHO FUNCTIONS

int		quotes_verify(char *argv);
char	**ft_split2(char *str, char c);
int		is_there_a_dollar(char *str);
int		echo_flag(char *argv);
int		echo_func(char *argv, int flag);
int		flag_count(char *argv);
int		in_between(char c, char *str, int i);
//void	is_there_dollar_sign(char *argv, t_shell *utils);

//CD Functions
char	*get_user(char **env, char *str, int i, int j);
char	*user_search(char **env, int i, int j, int len);
int		get_line_value(char **exp, int line);
int		is_twopoints(char *argv);
void	argc_1(t_cd *cd, char *home, int argc, char **argv);
void	argc_2(t_cd *cd, char **argv);
void	cd_initialize(t_cd *cd, t_shell *utils);
void	get_cd(t_cd *cd, char **argv);

//Env Functions

int		compare_exp_env(t_shell *utils, int i, int j);
void	build_env(int argc, char **argv, t_shell *utils);
void	write_exp_to_env(t_shell *utils, int i, int j);

//BUILTINS
char	**build_export(int argc, char **argv, t_shell *utils);
char	**build_unset(int argc, char **argv, char **exp, int i);
int		builtins(char *str, t_shell *utils, int i);
void	build_cd(int argc, char **argv, char **env, t_shell *utils);
void	build_echo(char *arr, t_shell *utils, int i, int j);
void	build_env(int argc, char **argv, t_shell *utils);
void	build_exit(char **argv, t_shell *utils);
void	build_pwd(int argc, char **argv, t_shell *utils);

//PID FUNCTIONS

char	*ft_getpid(void);
void	ft_free_pid(char **pid);

//SIGNALS
void	signal_search(t_signal_type t);

//Pipe Related

bool	is_there_pipe(char *str);
char	**pipping_commands(char *input);
char	**pipping_commands2(char *str, int x);
int		size_before_pipe(char *str);
int		pipe_verify(char *argv, int x);

//Expansion Related

void	handle_no_quotes_echo(t_shell *utils);
void	handle_quotes_echo(t_shell *utils);
char	*expansions(char *argv, t_shell *utils, int pa);
char	*ft_strjoinn(char *s1, char *s2);
int		is_there_a_dollar(char *str);
int		pid_dollar(char *str, int j);
int		varlen(char *str, int k);

//EXIT
void	final_cleaner(t_shell *utils);
void	free_dptr(char **clc);
void	ft_free(void **pointer);

//COMMANDS
int		builtin_not_command(char **argv);
void	execute_comm(char **argv, char *test2, t_shell *utils, char *test);
void	path_comms(char **argv, t_shell *utils, t_pipesort *piped);

//MiniShell Related

void	exec_builtin(int flag, char **command, char **env, t_shell *utils);
void	index_reset(t_shell *utils);
void	input_fixer(char *input);

//tokenizar a string, e depois usar o split para ...
//outros

void	free_pipesort(t_pipesort *head);
void	input_fixer(char *input);
size_t	len_dp(char **s);
char	*double_to_one(char **dptr);
int		where_is_echox(char **bizarre);
int		where_is_echoj(char ***bizarre);
void	exec_builtin(int flag, char **command, char **env, t_shell *utils);
void	index_reset(t_shell *utils);
bool	redirection_verifier_utils(t_pipesort *piped, int i, int j);
bool	redirection_verifier(t_pipesort *piped);
int		correct_redirection(char **dptr);
void	utils_init(t_shell *utils, char **env);
void	helper_lines(int argc, char **argv, t_shell *utils);
int		main(int argc, char **argv, char **env);
#endif