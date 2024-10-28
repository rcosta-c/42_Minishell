/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:35:22 by mota              #+#    #+#             */
/*   Updated: 2024/10/28 20:15:26 by mota             ###   ########.fr       */
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
static int  check_zeros(char *cmd)
{
    int i;

    i = -1;
    while (cmd && cmd[++i])
    {
        if (cmd[i] != '0')
            return (1);
    }
    return (0);
}

// Função para encerrar o shell, validando argumentos 
//e exibindo mensagens de erro apropriadas caso necessário
void    ft_exit(t_sh *sh, char **cmd)
{
    if (cmd[1] && cmd[2])
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: too many arguments\n", 2);
        sh->error.exit_error = true;
        return ;
    }
    else if (cmd[1] && !is_valid_number(cmd[1]))
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(cmd[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        sh->error.exit_error = true;
        return ;
    }
    else if (cmd[1] && check_zeros(cmd[1]))
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(cmd[1], 2);
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
