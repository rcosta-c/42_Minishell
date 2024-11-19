/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:22 by mota              #+#    #+#             */
/*   Updated: 2024/11/19 09:44:40 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Verifica se a string é um número válido
static int  is_valid_number(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (!ft_isdigit(str[i]) && str[i] == '+')
            return (0);
        i++;
    }
    return (1);
}

// Verifica se a string consiste apenas de zeros
static int  check_zeros(char *args)
{
    int i;

    i = -1;
    while (args && args[++i])
    {
        if (args[i] != '0')
            return (1);
    }
    return (0);
}

// Função para encerrar o shell, validando argumentos 
//e exibindo mensagens de erro apropriadas caso necessário
void    ft_exit(t_sh *sh, char **args)
{
    if (args[1] && args[2])
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: too many arguments\n", 2);
        sh->error.exit_error = true;
        return ;
    }
    else if (args[1] && !is_valid_number(args[1]))
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        sh->error.exit_error = true;
        return ;
    }
    else if (args[1] && check_zeros(args[1]))
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        sh->error.exit_error = true;
        return ;
    }
    else
    {
        ft_putstr_fd("exit\n", 2);
        sh->error.exit_error = false;
    }
}
