/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:56 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/13 10:54:57 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handbrake_and_exit(t_sh *sh)
{
	sh->vars.sh_status = false;
	g_status = EXIT_SIGQUIT;
	ft_exit(sh, NULL);	
}

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

	x = 0;
	if(sh->vars.cmds_num > 0)
	{
		while(x < sh->vars.cmds_num)
		{
			xx = 0;
			while(xx <= sh->comands[x].n_args)
				free(sh->comands[x].arg[xx++]);
			free(sh->comands[x].cmd);
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
