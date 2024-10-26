#include "../includes/minishell.h"

void	free_tokens(t_sh *sh)
{
	
	/*while(sh->vars.tk_num > 0)
	{
			free(&sh->tokens[sh->vars.tk_num].tokens);
			sh->vars.tk_num--;
	}*/
	free(sh->tokens);
}
