#include "minishell.h"

void    ckeck_pipe(char **cmd, t_sh *tokens)
{
    char    *input;

    input = NULL;
    if (!ft_strncmp(cmd, "|", 2))
    {
        input = readline("> ");
        if (input && !input[0])
        {
            input = free_ptr(input);
            return ;
        }
        parser(input, tokens);
        input = free_ptr(input);
    }
}