#include "../includes/minishell.h"

/*void	free_for_executer(t_sh *sh)
{
	free_tokens(sh);
	free(sh->cmd_line);

}*/


void	free_tokens(t_sh *sh)
{
	int x;

	x = 0;
	if(sh->vars.tk_num > 0)
	{
		while(x < sh->vars.tk_num)
		{
				free(sh->tokens[x].tokens);
				x++;
		}
		free(sh->tokens);
	}
}

void	free_cmds(t_sh *sh)
{
	int x;
	int	xx;

	xx = 0;
	x = 0;

	if(sh->vars.cmds_num > 0)
	{
		while(x < sh->vars.cmds_num)
		{
			free(sh->comands[x].cmd);
			while(xx <= sh->comands[x].n_args)
			{
				free(sh->comands[x].arg[xx]);
				xx++;
			}
//			free(sh->comands[x].arg[xx + 1]);
			free(sh->comands[x].arg);
			if(sh->comands[x].infile)
				free(sh->comands[x].infile);
			if(sh->comands[x].outappendfile)
				free(sh->comands[x].outappendfile);
			if(sh->comands[x].outfile)
				free(sh->comands[x].outfile);
			if(sh->comands[x].inheredoc_file)
				free(sh->comands[x].inheredoc_file);		
			x++;
		}
		free(sh->comands);
	}
	/*
	while(x < sh->vars.cmds_num && sh->vars.cmds_num > 0)
	{
		if(sh->comands[x].n_args > 0)
		{
			while(xx - 1 <= sh->comands[x].n_args)
			{
				free(sh->comands[x].arg[xx]);
				xx++;	
			}
			free(sh->comands[x].arg);
		}
		free(sh->comands[x].cmd);
		if(sh->comands[x].outfile)
			free(sh->comands[x].outfile);
		if(sh->comands[x].infile)
			free(sh->comands[x].infile);
		x++;
	}*/
}

void	free_env(t_sh *sh)
{
	int	x;

	x = 0;
	while(x < sh->vars.envp_total)
	{
		free(sh->envp[x]);
		x++;
	}
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

void	free_exit(t_sh *sh)
{
	free_tokens(sh);
	free_cmds(sh);
	if(sh->cmd_line)
		free(sh->cmd_line);
	free_env(sh);
	free(sh);
	rl_clear_history();
}
