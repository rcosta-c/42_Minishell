#ifndef MINISHELL_H
# define MINISHELL_H

#define DELIMITER "EOF"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <signal.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../lib/libft/libft.h"
#include "../lib/gnl/get_next_line_bonus.h"

# define OTHER_ERROR	1
# define SYNTAX_MISPELL	2
# define NO_PERMISSION	126
# define CMD_NOT_FOUND	127
# define EXIT_SIGINT	130
# define EXIT_SIGQUIT	131
# define WRONG_SYNTAX	258

//FALTAM MAIS AQUI em cima

extern int				g_status;

typedef struct s_vars
{
	bool	sh_status;
	int     tk_num;
	int		cmds_num;
	int		redir_num;
	int		heredoc_num;
	int		pipe_num;
	int		is_pipe;
	int		envp_total;
}   t_vars;


typedef struct s_tokens
{
	int     num;
	char    *tokens;
	bool    cmd;
	bool    arg;
	bool    pipe;
	bool    s_quote;
	bool    d_quote;
	bool    f_quote;
	bool    r_in;
	bool	r_heredoc;
	bool    r_out;
	bool	r_outappend;
	bool    file;
	bool    envp;
	bool    exp_t;      
	bool    exp_e;
}   t_tokens;

typedef struct s_error
{
	bool    exit_error;
	bool    cmd_error;
	bool	heredoc_error;
	bool    token_error;
	bool    expand_error;
	bool    parse_error;
	bool    exec_error;
}   t_error;

typedef struct s_execerror
{
	bool    cmd_not_found;
	bool    infile_notvalid;
	bool    infile_noaccess;
	bool    outfile_noaccess;
	bool    outfile_notvalid;
	bool	empty_pipe;
	bool	empty_redir;
}   t_execerror;

typedef struct s_exec
{
	int    		n_args;
	char   		*cmd;
	char   		**arg;
	char		*infile;
	char    	*outfile;
	char		*inheredoc_file;
	char    	*outappendfile;
	int			pipe_fd[2];
	bool		redir;
	bool		pipes;
	int			inheredoc_fd;
	int			infile_fd;
	int			outfile_fd;
	int			outappend_fd;
	int			outbackup;
	int			inbackup;
	t_execerror errors;

}   t_exec;

typedef struct s_sh
{
	t_exec      *comands;
	t_tokens    *tokens;
	t_vars      vars;
	char        *cmd_line;
	char        **envp;
	t_error     error;

}   t_sh;

/* PROMPT.c */
char	*get_prompt(t_sh *sh);
char	*join_2_str(char *a, char *b, char *z, int option);
/*   FIM   */


/*	PROMP_UTILS.c	*/

void	ft_getenv(t_sh *sh, char **envp);
char 	*find_my_host(t_sh *sh);
/*	FIM 	*/



/* FREE.c */
void	free_tokens(t_sh *sh);
char	**free_mat(char **mat);
char	*free_ptr(char *ptr);
void	free_cmds(t_sh *sh);
void	free_env(t_sh *sh);
void	free_exit(t_sh *sh);
void	free_for_executer(t_sh *sh);

/*   FIM   */

/*	ERRORS.c	*/

bool    verify_errors(t_sh *sh);

/*	FIM 	*/



/* INIT.c */
void	init_error(t_sh *sh);
void	init_tokens(t_sh *sh);
void	init_parser(t_sh *sh);

/*   FIM   */


/*	INIT_UTILS.c	*/

void	init_tk_flag1(t_sh *sh, int x);
void    init_cmds(t_sh *sh, int x);
void	init_vars(t_sh *sh);
/*		FIM 	*/


/*	SIGNALS.c	*/

void	ft_sigset(void);
void	ft_signal_handler(int sig);

/*	FIM		*/

/* TOKEN.c */
char *prepare_line(char *str);
int	count_tokens(t_sh *sh);
bool counter_validation(int c);
void	filter_tokens(t_sh *sh);
/*   FIM   */

/* SPLIT_CMD.c */
void	split_cmd(t_sh *sh);
/*   FIM   */

/* TOKEN_CHECKER.c */
bool token_is_valid(char *src);
int	check_dquote(char *str, int counter);
int	check_squote(char *str, int counter);
int check_type_quote(char *cmd_line, int x);
/*   FIM   */

/* TOKEN_CHECKER_UTILS.c */
bool	check_if_dquote(char *str, int x_o);
bool	check_if_squote(char *str, int x_o);
bool	search_ext(char *str);
/*   FIM   */

/* TOKEN_FILTER1.c */
void	filter_args (t_sh *sh, int n);
void	filter_envp(t_sh *sh, int n);
void	filter_cmds(t_sh *sh, int n);
void	filter_tokens(t_sh *sh);
/*   FIM   */


/* TOKEN_FILTER2.c */
void	filter_file (t_sh *sh, int n);
void	filter_pipes_redir(t_sh *sh, int n);
void	filter_quotes(t_sh *sh, int n);
/*   FIM   */


/* EXPANDER.c */
void	search_expand(t_sh *sh);
void	expand_token(t_sh *sh, char *token, int n);
char	*search_envp(t_sh *sh, char *z);

/*   FIM   */


/* PARSE.C*/
bool    check_before_parse(t_sh *sh);
void    fill_parser(t_sh *sh);
bool    check_r_out(t_sh *sh);
bool    check_r_in(t_sh *sh);
bool	check_r_append_out(t_sh *sh);

/*	FIM	   */


/*	REDIR.c		*/

void	handle_redirects(t_sh *sh, int x);

/*	FIM 	*/

/*	PARSE_UTILS.c	*/

int	parse_utils(t_sh *sh, int z, int n_cmd);
int	parse_pipes(t_sh *sh, int z, int n_cmd);
void	remove_quoted(t_sh *sh);

/*	FIM		*/

/*	HEREDOC.c	*/

char *handle_nextline_heredoc(int fd);
void handle_heredoc(t_sh *sh, int x);

/*	FIM		*/


/* BUILTINS.c */
void	ft_echo(t_sh *sh, char **args);
void	ft_pwd(t_sh *sh, char **args);
void	ft_cd(t_sh *sh, char **args);
void	ft_unset(t_sh *sh, char **args);
void	ft_exit(t_sh *sh, char **args);
void	ft_env(t_sh *sh, char **args);
void	ft_export(t_sh *sh, char **args);
/*   FIM   */


/*	EXECUTER.c	*/
void    execute_cmd(t_sh *sh, int x);
void	executor(t_sh *sh);
void    execute_multi_cmd(t_sh *sh, int x);

/*	FIM		*/


/*	EXECUTER_UTILS.c	*/
bool	check_if_builtin(char *cmd);
char    *prep_cmd(t_sh *sh, char *cmd, int x);
bool	check_exec_error(t_sh *sh, int x);
void    exec_builtin(t_sh *sh, int cmd_nbr);

/*	FIM		*/

/*	PIPE.c*/
void	start_pipes(t_sh *sh);
void	close_pipe_child(t_sh *sh);
void	execute_pipeline(t_sh *sh, int n_cmds);
void create_pipes(t_sh *sh, int ***pipes);
void	close_pipes(int **pipes, int pipe_num);
void setup_pipes(int **pipes, int i, int cmds_num);
void	check_pipes(t_sh *sh);
/*	FIM		*/

#endif