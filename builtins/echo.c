/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:26:11 by mota              #+#    #+#             */
/*   Updated: 2024/11/19 09:44:17 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Função que imprime os argumentos passados, 
//com suporte para omitir a nova linha final se a flag -n for utilizada
void    ft_echo(t_sh *sh, char **args)
{
    int i;
    int n_flag;

    i = 1;
    n_flag = 0;
    if (args[1] && !ft_strncmp(args[1], "-n", 2))
    {
        n_flag = 1;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);
    sh->error.exit_error = false;
}