#include "../includes/minishell.h"

void    free_heredoc(t_sh *sh)
{
	int	x;

	x = 0;
	if(sh->vars.heredoc_num == 0)
		return;
	else
	{
		while(x < sh->vars.heredoc_num)
		{
			free(sh->comands[x].infile)
		}





	}
		printf("fazer o handle do freehereder\n\n");

}