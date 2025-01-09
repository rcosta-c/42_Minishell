/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 11:42:42 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/01/09 22:32:50 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h> 
# include <signal.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"

# define ERROR_FD		-1
# define BUILTINSERROR	1
# define SYNTAX_MISPELL	2
# define NO_PERMISSION	126
# define CMD_NOT_FOUND	127
# define ENV_VAR_NOT_FOUND 128
# define EXIT_SIGINT	130
# define EXIT_SIGQUIT	131
# define CONAS			77
# define WRONG_SYNTAX	258

extern int				g_status;

typedef struct s_vars
{
	bool	sh_status;
	int		tk_num;
	int		cmds_num;
	int		redir_tot;
	int		heredoc_num;
	int		pipe_num;
	int		is_pipe;
	int		envp_total;
	int		history_n;
	char	*sh_user;
	char	*sh_home;
	char	*sh_pwd;
	char	*sh_host;
	char	*minihome;
}	t_vars;

typedef struct s_tokens
{
	int		num;
	char	*tokens;
	bool	cmd;
	bool	arg;
	bool	pipe;
	bool	s_quote;
	bool	d_quote;
	bool	f_quote;
	bool	r_in;
	bool	r_heredoc;
	bool	r_out;
	bool	r_outappend;
	bool	file;
	bool	envp;
	bool	exp_t;
	bool	exp_e;
	bool	exp_empty;
}	t_tokens;

typedef struct s_error
{
	bool	exit_error;
	bool	cmd_error;
	bool	heredoc_error;
	bool	token_error;
	bool	expand_error;
	bool	parse_error;
	bool	exec_error;
}	t_error;

typedef struct s_execerror
{
	bool	cmd_not_found;
	bool	infile_notvalid;
	bool	infile_noaccess;
	bool	outfile_noaccess;
	bool	outfile_notvalid;
	bool	empty_pipe;
	bool	empty_redir;
}	t_execerror;

typedef struct s_exec
{
	char		*cmd;
	char		**arg;
	char		*infile;
	char		*outfile;
	char		*inheredoc_file;
	char		*outappendfile;
	bool		redir;
	bool		pipes;
	bool		heredoc;
	bool		app_out;
	int			n_redir;
	int			n_args;
	int			inheredoc_fd;
	int			infile_fd;
	int			outfile_fd;
	int			outbackup;
	int			inbackup;
	t_execerror	errors;

}	t_exec;

typedef struct s_sh
{
	char		temp[500][500];
	t_exec		*comands;
	t_tokens	*tokens;
	t_vars		vars;
	char		*cmd_line;
	char		**envp;
	t_error		error;

}	t_sh;

/* PROMPT.c */
char	*get_prompt(t_sh *sh);
char	*join_2_str(char *a, char *b, char *z, int option);
char	*verify_home(t_sh *sh, char *prompt);
int		verify_helper(t_sh *sh, char *prompt, int x);
/*   FIM   */

/*	PROMP_UTILS.c	*/
void	ft_getenv(t_sh *sh, char **envp);
char	*find_my_host(t_sh *sh);
bool	multiquote_checker(int counter_s, int counter_d);
/*	FIM 	*/

/* FREE.c */
void	free_tokens(t_sh *sh);
char	**free_mat(char **mat);
char	*free_ptr(char *ptr);
void	free_cmds(t_sh *sh);
void	free_env(t_sh *sh);
void	free_exit(t_sh *sh);
void	free_for_executer(t_sh *sh);
void	handbrake_and_exit(t_sh *sh);
/*   FIM   */

/*	ERRORS.c	*/
bool	filter_cmd_error(t_sh *sh);
bool	verify_errors(t_sh *sh);
/*	FIM 	*/

/*	ERROR_UTILS1.c*/
bool	check_directory_error(t_sh *sh, int x);
bool	filter_tk_error_exit(t_sh *sh);
bool	check_access_error(t_sh *sh, int x);
bool	check_file_error(t_sh *sh, int x);
bool	check_env_var_error(t_sh *sh, int x);
/*	FIM 	*/

/*	ERROR_UTILS2.c 	*/
bool	verify_error_exit(int option);
bool	verify_error_helper(t_sh *sh, int x);
/*	FIM		*/

/* INIT.c */
void	init_error(t_sh *sh);
void	init_tokens(t_sh *sh);
void	init_parser(t_sh *sh);
void	init_cycle(t_sh *sh);
/*   FIM   */

/*	INIT_UTILS.c	*/
void	init_tk_flag1(t_sh *sh, int x);
void	init_cmds(t_sh *sh, int x);
void	init_vars(t_sh *sh);
void	init_prompt_utils(t_sh *sh);
/*		FIM 	*/

/*	SIGNALS.c	*/
void	ft_sigset(void);
void	ft_sigset_fd(void);
void	ft_signal_handler(int sig);
void	ft_signal_handfd(int sig);
/*	FIM		*/

/* TOKEN.c */
char	*prepare_line(char *str);
void	filter_tokens(t_sh *sh);
/*   FIM   */

/* TOKEN_COUNTER.c */
void	count_tokens(t_sh *sh);
bool	counter_validation(int c);

/*   FIM   */

/* TOKEN_COUNTER.c */
void	copy_tokens(t_sh *sh);
/*	FIM		*/

/* TOKEN_CHECKER.c */
bool	verify_cmdline(t_sh *sh, char *cmdline);
bool	token_is_valid(char src);
int		check_dquote(char *str, int counter);
int		check_squote(char *str, int counter);
int		check_type_quote(char *cmd_line, int x);
/*   FIM   */

/* TOKEN_CHECKER_UTILS.c */
bool	check_if_dquote(char *str, int x_o);
bool	check_if_squote(char *str, int x_o);
bool	search_ext(char *str);
/*   FIM   */

/*	TOKEN_UTILS.c*/
bool	check_if_special_redir(char *str, int x);
bool	check_if_special_redirout(char *str, int x);
bool	check_if_special_redirin(char *str, int x);
void	ft_give_some_space(char *str, char *temp, int *x_o, int *x_d);
bool	check_if_pipe(char *str, int x_o);
/*	FIM		*/

/* TOKEN_FILTER1.c */
void	filter_args(t_sh *sh, int n);
void	filter_envp(t_sh *sh, int n);
void	filter_cmds(t_sh *sh, int n);
void	filter_tokens(t_sh *sh);
/*   FIM   */

/* TOKEN_FILTER2.c */
void	filter_file(t_sh *sh, int n);
void	filter_pipes_redir(t_sh *sh, int n);
void	filter_quotes(t_sh *sh, int n);
/*   FIM   */

/* TOKEN_FILTER2.c */
void	filter_args_checker(t_sh *sh, int n);
int		filter_envp_helper(t_sh *sh, int n, int x);
void	filter_quotes_helper(t_sh *sh, int n, int counter_s, int counter_d);
/*	FIM 	*/

/* EXPANDER.c */
void	search_expand(t_sh *sh);
void	expand_token(t_sh *sh, int n);
char	*expand_token_seeker(t_sh *sh, int *x, int n);
char	*expand_token_seeker2(t_sh *sh, int *x, int n, char *c);
char	*pre_expand(t_sh *sh, int *x, int n);
/*   FIM   */

/*	EXPANDER_UTILS.c*/
int		count_expands(t_sh *sh, int n);
char	*search_envp(t_sh *sh, char *z);
int		ft_envp_n_cmp(const char *s1, const char *s2);
char	*expand_exit(t_sh *sh, int n, int x, char *z);
char	*expand_exit_token(t_sh *sh, int *x, int n, char *c);

/*	FIM 	*/

/* PARSE.C*/
void	fill_parser(t_sh *sh);
int		parse_pipes(t_sh *sh, int z, int n_cmd);
/*	FIM	   */

/*	REDIR.c		*/
void	handle_redirects(t_sh *sh, int x);
/*	FIM 	*/

/*	PARSE_UTILS.c	*/
int		parse_no_cmds(t_sh *sh, int n_cmd, int x);
int		parse_no_args(t_sh *sh, int n_cmd, int x);
int		parse_with_args(t_sh *sh, int n_cmd, int x);
int		parse_utils(t_sh *sh, int x, int n_cmd);
bool	ft_if_redir(t_sh *sh, int x);
/*	FIM		*/

/*	PARSE_UTILS2.c	*/
bool	check_before_parse(t_sh *sh);
void	ft_easyfix_command(t_sh *sh, int n_cmd);
bool	check_r_out(t_sh *sh);
bool	check_r_in(t_sh *sh);
bool	check_r_append_out(t_sh *sh);
/*	FIM		*/

/* PARSE_UTILS_QUOTES.c 	*/
char	*clean_quote_d(t_sh *sh, int n);
char	*clean_quote_s(t_sh *sh, int n);
void	remove_quoted(t_sh *sh);
/*		FIM		*/

/*	REDIR_PARSE	*/

void	ft_redir_multiargs(t_sh *sh);
/*	FIM 	*/

/*	REDIR_PARSE2	*/
void	ft_count_redirs(t_sh *sh, int x, int n_cmd);
int		ft_parse_redirs(t_sh *sh, int x, int n_cmd);
int		count_dpoint(char **ptr);
/*	FIM 	*/

/*	HEREDOC.c	*/
char	*handle_nextline_heredoc(int fd);
void	handle_heredoc(t_sh *sh, int x);
/*	FIM		*/

/* BUILTINS.c */
void	ft_echo(t_sh *sh, char **args);
void	ft_pwd(t_sh *sh, char **args);
void	ft_cd(t_sh *sh, char **args);
void	ft_unset(t_sh *sh, char **args);
void	ft_exit(t_sh *sh, char **args);
void	ft_env(t_sh *sh, char **args);
void	ft_export(t_sh *sh, char **args);
int		get_var_pos(t_sh *sh, char *var);
void	update_var(t_sh *sh, char *var);
void	display_exported_vars(t_sh *sh);
char	**handle_array(t_sh *sh);
void	free_temp_env(char **temp);
bool	update_old_pwd(t_sh *sh, char *old_pwd);
char	*going_dir_up(char *oldpwd);
/*   FIM   */

/*	EXECUTER.c	*/
void	execute_cmd(t_sh *sh, int x);
void	executor(t_sh *sh);
void	execute_multi_cmd(t_sh *sh, int x);
/*	FIM		*/

/*	EXECUTER_UTILS.c	*/
bool	check_if_builtin(char *cmd);
char	*prep_cmd(t_sh *sh, char *cmd, int x);
bool	check_exec_error(t_sh *sh, int x);
void	exec_builtin(t_sh *sh, int cmd_nbr);
/*	FIM		*/

/*	PIPE.c*/
void	execute_pipeline(t_sh *sh, int i);
void	check_pipes(t_sh *sh);
/*	FIM		*/

/*	PIPE.c*/
void	get_out_of_pipe(void);
void	prep_cmds_pipes(t_sh *sh);
void	pipeline_exit(t_sh *sh, int in_fd, int i);
/*	FIM		*/

/*	HISTORY.c	*/
void	save_to_history(t_sh *sh, char *cmd_line);
int		count_history_entries(t_sh *sh);
/*	FIM	*/

#endif
