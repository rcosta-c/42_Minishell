/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:39:54 by mota              #+#    #+#             */
/*   Updated: 2024/11/18 19:54:26 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Exibe todas as variáveis de ambiente, 
//ou uma mensagem de erro caso haja argumentos adicionais
void    ft_env(t_sh *sh, char **cmd)
{
    size_t i;

    if (cmd[1])
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(cmd[1], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        sh->error.exit_error = true;
        return ;
    }
    else
    {
        i = 0;
        while (sh->envp && sh->envp && sh->envp[0][i])
        {
            ft_putstr_fd(sh->envp[i], 1);
            ft_putstr_fd("\n", 1);
            i++;
        }
        sh->error.exit_error = false;
    }
}