#include "../includes/minishell.h"

void	free_tokens(t_sh *sh)
{
	int x;

	x = 0;	
	while(x < sh->vars.tk_num - 1)
	{
			free(sh->tokens[x].tokens);
			x++;
	}
	free(sh->tokens);
}

void	free_cmds(t_sh *sh)
{
	int x;
	int	xx;

	xx = 0;
	x = 0;
	while(x < sh->vars.cmds_num)
	{
		if(sh->comands[x].n_args > 0)
		{
			while(xx < sh->comands[x].n_args)
			{
				free(sh->comands[x].arg[xx++]);	
			}
			free(sh->comands[x].arg);
		}
		free(sh->comands[x].cmd);
		if(sh->comands[x].outfile)
			free(sh->comands[x].outfile);
		if(sh->comands[x].infile)
			free(sh->comands[x].infile);
		x++;
	}
}

void	free_env(t_sh *sh)
{/*
	int	x;

	x = 0;
	while(x < sh->vars.envp_total)
	{
		free(sh->envp[x]);
		x++;
	}*/
	/*while(x >= 0)
	{
		free(sh->envp[x--]);
	}*/
	free(sh->envp);
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
