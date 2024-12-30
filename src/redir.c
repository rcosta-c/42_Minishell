/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:53:18 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 18:32:38 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_redir_in(t_sh *sh, int x)
{
	if (sh->comands[x].heredoc == true)
	{
		handle_heredoc(sh, x);
	}
	sh->comands[x].infile_fd = open(sh->comands[x].infile, O_RDONLY);
	if (sh->comands[x].infile_fd < 0)
	{
		sh->comands[x].errors.infile_notvalid = true;
		perror("Minishell: ");
		return ;
	}
	sh->comands[x].inbackup = dup(STDOUT_FILENO);
	if (dup2(sh->comands[x].infile_fd, STDIN_FILENO) < 0)
	{
		perror("Erro ao redirecionar stdin");
		close(sh->comands[x].infile_fd);
		return ;
	}
	close(sh->comands[x].infile_fd);
}

static void	handle_redir_out(t_sh *sh, int x)
{
	sh->comands[x].outfile_fd = open(sh->comands[x].outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sh->comands[x].outfile_fd < 0)
	{
		sh->comands[x].errors.outfile_notvalid = true;
		perror("erro ao abrir output_fd");
		return ;
	}
	sh->comands[x].outbackup = dup(STDOUT_FILENO);
	if (dup2(sh->comands[x].outfile_fd, STDOUT_FILENO) < 0)
	{
		perror("Erro ao redirecionar stdout");
		close(sh->comands[x].outfile_fd);
		return ;
	}
	close(sh->comands[x].outfile_fd);
}

static void	handle_redir_outapp(t_sh *sh, int x)
{
	sh->comands[x].outappend_fd = open(sh->comands[x].outappendfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (sh->comands[x].outappend_fd < 0)
	{
		sh->comands[x].errors.outfile_notvalid = true;
		perror("erro ao abrir output_fd");
		return ;
	}
	sh->comands[x].outbackup = dup(STDOUT_FILENO);
	if (dup2(sh->comands[x].outappend_fd, STDOUT_FILENO) < 0)
	{
		perror("Erro ao redirecionar stdout");
		close(sh->comands[x].outappend_fd);
		return ;
	}
	close(sh->comands[x].outappend_fd);
}

void	handle_redirects(t_sh *sh, int x)
{
	if (sh->comands[x].redir == false)
		return ;
	if (sh->comands[x].infile)
		handle_redir_in(sh, x);
	if (sh->comands[x].outfile)
		handle_redir_out(sh, x);
	if (sh->comands[x].outappendfile)
		handle_redir_outapp(sh, x);
}
