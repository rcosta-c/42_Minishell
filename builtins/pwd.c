/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:59:34 by mota              #+#    #+#             */
/*   Updated: 2024/11/18 20:01:33 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//imprime o diretório de trabalho atual,
// ou exibe uma mensagem de erro caso não consiga acessá-lo
void    ft_pwd(t_sh *sh, char **cmd)
{
    size_t  i;

    if (!cmd[1])
    {
        i = 0;
        while (sh->envp && ft_strncmp(sh->envp[i], "PWD=", 4))
            i++;
        if (sh->envp && sh->envp[i])
        {
            ft_putstr_fd(sh->envp[i][4], 1);
            ft_putstr_fd("\n", 1);
        }
        else
        {
            ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
            sh->error.exit_error = true;
        }
    }
}
