/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:55:24 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/10 19:57:42 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	after_execution(t_sh *sh, int pid)
{
	int	status;

	(void)sh;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = 128 + WTERMSIG(status);
}
