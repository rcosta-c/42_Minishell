#include "../includes/minishell.h"

void	free_tokens(t_sh *sh)
{
	/*int x;

	x = 0;	
	while(x < sh->vars.tk_num - 1)
	{
			free(&sh->tokens[x].tokens);
			x++;
	}*/
	free(sh->tokens);
}
