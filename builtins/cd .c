/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd .c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:35:59 by mota              #+#    #+#             */
/*   Updated: 2024/10/28 11:54:13 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void set_dir(t_sh *sh, char *dir, char **envp)
{
    char    *temp;
    char    *var;

    temp = NULL;
    var = ft_calloc(3, sizeof(char *));
    var[0] = ft_strjoin("export", var);
    temp = getcwd(temp, BUFFER_SIZE);
    if (chdir (dir))
    {
        perror;
        sh->error.exit_error = true;
    }
    else
    {
        var[1] = ft_strjoin("OLDPWD=", temp);
        ft_export(sh, var, envp);
        free(temp);
        free(var[1]);
        temp = getcwd(temp, BUFFER_SIZE);
        var[1] = ft_strjoin("PWD=", temp);
        ft_export(sh, var, envp);
        sh->error.exit_error = false;
    }
    free(temp);
    free(var);
}

static void *set_home(t_sh *sh, char **envp)
{
    char    *home;

    while (envp &&  ft_strncmp(envp[0], "HOME=", 5))
        envp++;
    home = *envp + 5;
    return (home);
}

void    ft_cd(t_sh *sh, char **cmd, char **envp)
{
    if (cmd[1] && !cmd[2])
        set_dir(sh, cmd[1], envp);
    else if (!cmd[1])
        set_dir(sh, set_home (sh, envp), envp);
    else
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        sh->error.exit_error = true;
    }
}