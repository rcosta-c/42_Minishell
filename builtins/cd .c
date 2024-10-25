/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd .c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:35:59 by mota              #+#    #+#             */
/*   Updated: 2024/10/25 22:18:22 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void set_dir(t_mini *mini, char *dir, char **envp)
{
    char    *temp;
    char    *var;

    temp = NULL;
    var = ft_calloc(3, sizeof(char *));
    var[0] = ft_strjoin("export");
    temp = getcwd(temp, BUFFER_SIZE);
    if (chdir (dir))
    {
        perror;
        mini->exit = 1;
    }
    else
    {
        var[1] = ft_strjoin("OLDPWD=", temp);
        ft_export(mini, var, envp);
        free(temp);
        free(var[1]);
        temp = getcwd(temp, BUFFER_SIZE);
        var[1] = ft_strjoin("PWD=", temp);
        ft_export(mini, var, envp);
        mini -> error = 0;
    }
    free(temp);
    free(var);
}

static void *set_home(t_mini *mini, char **envp)
{
    char    *home;

    while (envp &&  ft_strncmp(envp[0], "HOME=", 5))
        envp++;
    home = *envp + 5;
    return (home);
}

void    ft_cd(t_mini *mini, char **cmd, char **envp)
{
    if (cmd[1] && !cmd[2])
        set_dir(mini, cmd[1], envp);
    else if (!cmd[1])
        set_dir(mini, set_home (mini, envp), envp);
    else
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        mini->error = 1;
    }
}