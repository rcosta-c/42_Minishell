/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:53:12 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/30 14:54:37 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigset(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	ft_sigset_fd(void)
{
	signal(SIGINT, ft_signal_handfd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(0, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signal_handfd(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
	}
}
