/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:59:34 by mota              #+#    #+#             */
/*   Updated: 2024/10/28 11:51:02 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_pwd(t_sh *sh, char **cmd, char **envp)
{
    size_t  i;

    if (!cmd[1])
    {
        i = 0;
        while (envp && ft_strncmp(envp[i], "PWD=", 4))
            i++;
        if (envp && envp[i])
        {
            ft_putstr_fd(&envp[i][4], 1);
            ft_putstr_fd("\n", 1);
        }
        else
        {
            ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
            sh->error.exit_error = true;
        }
    }
}
