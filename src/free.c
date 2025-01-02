/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:56 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/02 00:34:19 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_sh *sh)
{
	int	x;

	x = 0;
	if (sh->vars.tk_num > 0)
	{
		while (x <= sh->vars.tk_num)
		{
			free(sh->tokens[x].tokens);
			x++;
		}
		free(sh->tokens);
		x = 0;
		while (x < 50)
			ft_bzero(sh->temp[x++], sizeof(char *));
	}
}

void	free_cmds_helper(t_sh *sh, int x)
{
	if (sh->comands[x].infile)
		free(sh->comands[x].infile);
	if (sh->comands[x].outappendfile)
		free(sh->comands[x].outappendfile);
	if (sh->comands[x].outfile)
		free(sh->comands[x].outfile);
	if (sh->comands[x].inheredoc_file)
		free(sh->comands[x].inheredoc_file);
	if (sh->comands[x].inbackup != -1)
	{
		dup2(sh->comands[x].inbackup, STDIN_FILENO);
		sh->comands[x].infile_fd = -1;
		close(sh->comands[x].inbackup);
	}
	if (sh->comands[x].outbackup != -1)
	{
		dup2(sh->comands[x].outbackup, STDOUT_FILENO);
		sh->comands[x].outfile_fd = -1;
		close(sh->comands[x].outbackup);
	}
}

void	free_cmds(t_sh *sh)
{
	int	x;
	int	xx;

	x = 0;
	if (sh->vars.cmds_num > 0)
	{
		while (x < sh->vars.cmds_num)
		{
			xx = 0;
			while (xx <= sh->comands[x].n_args)
				free(sh->comands[x].arg[xx++]);
			free(sh->comands[x].cmd);
			free(sh->comands[x].arg);
			free_cmds_helper(sh, x);
			x++;
		}
		free(sh->comands);
	}
}

void	free_env(t_sh *sh)
{
	int	x;

	x = 0;
	while (x < sh->vars.envp_total)
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
	if (sh->cmd_line)
		free(sh->cmd_line);
	free_env(sh);
	free(sh->vars.sh_host);
	free(sh->vars.sh_pwd);
	free(sh->vars.sh_user);
	free(sh->vars.sh_home);
	free(sh->vars.minihome);
	free(sh);
	if (access(".heredoc_temp.txt", F_OK) == 0)
		unlink(".heredoc_temp.txt");
	rl_clear_history();
}
