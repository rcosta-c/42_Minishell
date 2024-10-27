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

char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	**free_mat(char **mat)
{
	size_t	i;

	i = 0;
	while (mat && mat[i])
	{
		mat[i] = free_ptr(mat[i]);
		i++;
	}
	free (mat);
	mat = NULL;
	return (NULL);
}