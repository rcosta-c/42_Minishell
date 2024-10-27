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
    int     tk_num; //numero total de tokens
}   t_vars;


typedef struct s_tokens
{
    int     num;        //num do token
    char    *tokens;    //conteudo do token
    bool    **cmd;                            // flags para definir o tipo de token
    bool    arg;                            // flags para definir o tipo de token.
    bool    pipe;                            // flags para definir o tipo de token.
    bool    s_quote;                            // flags para definir o tipo de token.
    bool    d_quote;                            // flags para definir o tipo de token.
    bool    f_quote;                            // flags para definir o tipo de token.
    bool    r_in;                            // flags para definir o tipo de token.
    bool    r_out;                            // flags para definir o tipo de token.
    bool    file;                            // flags para definir o tipo de token.
    bool    **envp;                            // flags para definir o tipo de token.
}   t_tokens;

typedef struct s_error                //struct apenas para assinalar erros
{
    bool    exit_error;
    bool    cmd_error;
    bool    token_error;
    bool    expand_error;
    bool    parse_error;
    bool    exec_error;
}   t_error;

typedef struct s_sh            //struct principal, onde esta as ligacoes para todas as outras estruturas existentes
{
    t_tokens    *tokens;
    t_vars      vars;
    char        *cmd_line;
    t_error     error;

}   t_sh;

/*             FUNCTIONS           */

/* PROMPT.c */
char	*get_prompt();
/*    FIM     */

/* TOKEN_CHECKER.c */
bool token_is_valid(char *src);
int	check_dquote(char *str, int counter);
int	check_squote(char *str, int counter);
int check_type_quote(char *cmd_line, int x);
/*   FIM   */

/* FREE.c */
void	free_tokens(t_sh *sh);
char	*free_ptr(char *ptr);
char	**free_mat(char **mat);
/*   FIM   */

/* INIT.c */
void	init_error(t_sh *sh);
void	init_tokens(t_sh *sh);
/*   FIM   */

/* TOKEN.c */
static char *prepare_line(char *str);
static char	*ft_2strdup(const char *s);
static int	count_tokens(t_sh *sh);
static bool counter_validation(int c);
void	filter_tokens(t_sh *sh);
void	split_cmd(t_sh *sh);
/*   FIM   */

/* TOKEN_CHECKER_UTILS.c */
bool	check_if_dquote(char *str, int x_o);
bool	check_if_squote(char *str, int x_o);
bool	search_ext(char *str);
/*   FIM   */

// builtins
void    ft_echo(t_sh *sh, char **cmd);
void    ft_pwd(t_sh *sh, char **cmd, char **envp);
void    ft_cd(t_sh *sh, char **cmd, char **envp);
void    ft_unset(t_sh *sh, char **cmd, char **envp);
/*   FIM   */

#endif
