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

typedef struct s_shvars
{
    char    *temp_line;
    char    **cmds;
    char    **cmd_args;
    bool    pipe;
    bool    redirect;
    bool    cmd_error;
    int     n_cmds;
    int     n_pipes;
    int     n_redirect;
    int     cmd_len;

}   t_shvars;

typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**envp;
	t_tokens	*tokens;
	char	error;
	char	exit;
}	t_mini;


typedef struct s_tokens
{
    char    **tokens;
    char    **args;
    bool    pipe;
    bool    redirect;
    int     tk_num;


}   t_tokens;

/* builtins
void    ft_echo(t_sh *sh, char **cmd);
void    ft_pwd(t_sh *sh, char **cmd, char **envp);
void    ft_cd(t_sh *sh, char **cmd, char **envp);
void    ft_unset(t_sh *sh, char **cmd, char **envp);*/

char	*get_prompt();
void    get_tokens(char *str, t_shvars sh);


#endif