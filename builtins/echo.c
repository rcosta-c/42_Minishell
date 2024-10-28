/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:26:11 by mota              #+#    #+#             */
/*   Updated: 2024/10/28 11:50:51 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_echo(t_sh *sh, char **cmd)
{
    int i;
    int n_flag;

    i = 1;
    n_flag = 0;
    if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
    {
        n_flag = 1;
        i++;
    }
    while (cmd[i])
    {
        ft_putstr_fd(cmd[i], 1);
        if (cmd[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);
    sh->error.exit_error = false;
}