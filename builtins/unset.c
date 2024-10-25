/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:16:01 by mota              #+#    #+#             */
/*   Updated: 2024/10/25 23:23:25 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_unset(t_mini *mini, char **cmd, char **envp)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (cmd[i])
        i++;
    envp = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (mini->envp[i])
    {
        if (ft_strncmp(mini->envp[i], cmd[1], ft_strlen(cmd[1])) != 0)
        {
            envp[j] = ft_strdup(mini->envp[i]);
            j++;
        }
        i++;
    }
    envp[j] = NULL;
    free(mini->envp);
    mini->envp = envp;
}