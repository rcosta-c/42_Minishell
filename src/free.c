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

/*liberar memoria para um unico ponteiro*/
char	*free_ptr(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

/*liberar memoria para uma matriz de ponteiros*/
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
