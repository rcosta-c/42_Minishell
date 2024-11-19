/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:35:59 by mota              #+#    #+#             */
/*   Updated: 2024/11/19 09:50:05 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Função que altera o diretório de trabalho atual 
//e atualiza as variáveis de ambiente PWD e OLDPWD
static void set_dir(t_sh *sh, char *dir)
{
    char    *temp;
    char    *var;

    temp = NULL;
    var = ft_calloc(3, sizeof(char *));
    var[0] = *ft_strjoin("export", var);
    temp = getcwd(temp, BUFFER_SIZE);
    if (chdir (dir))
    {
        perror;
        sh->error.exit_error = true;
        //erro 
    }
    else
    {
        var[1] = *ft_strjoin("OLDPWD=", temp);
        ft_export(var, sh->envp);
        free(temp);
        free(var[1]);
        temp = getcwd(temp, BUFFER_SIZE);
        var[1] = *ft_strjoin("PWD=", temp);
        ft_export(var, sh->envp);
        sh->error.exit_error = false;
    }
    free(temp);
    free(var);
}

// Função que retorna o caminho do diretório 
// HOME a partir das variáveis de ambiente
static void *set_home(t_sh *sh)
{
    char    *home;

    while (sh->envp &&  ft_strncmp(sh->envp[0], "HOME=", 5))
        sh->envp++;
    home = *sh->envp + 5;
    return (home);
}

// Função que muda o diretório de trabalho, 
// seja para um especificado ou para o HOME se nenhum for dado
void    ft_cd(t_sh *sh, char **args)
{
    if (args[1] && !args[2])
        set_dir(args[1], sh->envp);
    else if (!args[1])
        set_dir(set_home (sh->envp), sh->envp);
    else
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        sh->error.exit_error = true;
    }
}