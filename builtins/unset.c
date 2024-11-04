/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:16:01 by mota              #+#    #+#             */
/*   Updated: 2024/10/28 20:10:32 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_unset(t_sh *sh, char **cmd)
{
    int i;
    int j;
    int k;
    char    *envx;

    i = 0;
    j = 0;
    k = 0;
    while (cmd[i])
        i++;
    envx = malloc(sizeof(char *) * (i + 1));
    i = 0;
    // Copia as variáveis de ambiente para 'envx', ignorando aquela especificada em 'cmd[1]'
    while (sh->envp[i])
    {
        if (ft_strncmp(sh->envp[i], cmd[1], ft_strlen(cmd[1])) != 0)
        {
            envx[j] = ft_strdup(sh->envp[i]);
            j++;
        }
        i++;
    }
    envx[j] = NULL;
    // Atualiza o ponteiro 'envp' com o novo array de variáveis de ambiente, sem a variável removida
    // free(sh->envx);
    sh->envp = envx;
}