#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../lib/libft/libft.h"

typedef struct s_vars
{
    int     tk_num;
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
    bool    r_out;
    bool    file;
    bool    envp;
    bool    exp_t;      
    bool    exp_e;
}   t_tokens;

typedef struct s_error
{
    bool    exit_error;
    bool    cmd_error;
    bool    token_error;
    bool    expand_error;
    bool    parse_error;
    bool    exec_error;
}   t_error;

typedef struct s_exec
{
    int     n_cmd;
    char    **cmd;
    char    **arg;
    int     infile;
    int     outfile;

}   t_exec;

typedef struct s_sh
{
    t_exec      **comands;
    t_tokens    *tokens;
    t_vars      vars;
    char        *cmd_line;
    char        **envp;
    t_error     error;

}   t_sh;

/* PROMPT.c */
char	*get_prompt();
void    get_tokens(t_sh *sh);
char	*join_2_str(char *a, char *b, char *z);
/*   FIM   */

/* FREE.c */
void	free_tokens(t_sh *sh);
/*   FIM   */

/* INIT.c */
void	init_error(t_sh *sh);
void	init_tokens(t_sh *sh);
/*   FIM   */

/* TOKEN.c */
char *prepare_line(char *str);
int	count_tokens(t_sh *sh);
bool counter_validation(int c);
void	filter_tokens(t_sh *sh);
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
/*   FIM   */



#endif