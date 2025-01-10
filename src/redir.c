/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:53:18 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/10 11:33:23 by rcosta-c         ###   ########.fr       */
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
		perror("Error opening stdin");
		return ;
	}
	sh->comands[x].inbackup = dup(STDIN_FILENO);
	if (dup2(sh->comands[x].infile_fd, STDIN_FILENO) < 0)
	{
		perror("Error redirecting stdin");
		close(sh->comands[x].infile_fd);
		return ;
	}
	close(sh->comands[x].infile_fd);
}

static void	cleanup_redir_out(t_sh *sh, int x)
{
	sh->comands[x].errors.outfile_notvalid = true;
	if (sh->comands[x].outfile_fd >= 0)
	{
		close(sh->comands[x].outfile_fd);
		sh->comands[x].outfile_fd = ERROR_FD;
	}
	if (sh->comands[x].outbackup >= 0)
	{
		dup2(sh->comands[x].outbackup, STDOUT_FILENO);
		close(sh->comands[x].outbackup);
		sh->comands[x].outbackup = ERROR_FD;
	}
}

static int	open_output_file(t_sh *sh, int x)
{
	int	fd;

	if (sh->comands[x].app_out == true)
	{
		fd = open(sh->comands[x].outfile,
				O_WRONLY | O_CREAT | O_APPEND,
				0666);
	}
	else
	{
		fd = open(sh->comands[x].outfile,
				O_WRONLY | O_CREAT | O_TRUNC,
				0666);
	}
	return (fd);
}

static void	handle_redir_out(t_sh *sh, int x)
{
	sh->comands[x].outfile_fd = ERROR_FD;
	sh->comands[x].outbackup = ERROR_FD;
	sh->comands[x].outfile_fd = open_output_file(sh, x);
	if (sh->comands[x].outfile_fd < 0)
	{
		perror("Error opening output file");
		cleanup_redir_out(sh, x);
		return ;
	}
	sh->comands[x].outbackup = dup(STDOUT_FILENO);
	if (sh->comands[x].outbackup < 0)
	{
		perror("Error backing up stdout");
		cleanup_redir_out(sh, x);
		return ;
	}
	if (dup2(sh->comands[x].outfile_fd, STDOUT_FILENO) < 0)
	{
		perror("Error redirecting stdout");
		cleanup_redir_out(sh, x);
		return ;
	}
	close(sh->comands[x].outfile_fd);
	sh->comands[x].outfile_fd = ERROR_FD;
}

void	handle_redirects(t_sh *sh, int x)
{
	if (sh->comands[x].redir == false)
		return ;
	if (sh->comands[x].infile)
		handle_redir_in(sh, x);
	if (sh->comands[x].outfile)
		handle_redir_out(sh, x);
}
