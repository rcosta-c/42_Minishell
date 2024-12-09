/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:16:01 by mota              #+#    #+#             */
/*   Updated: 2024/12/05 12:37:55 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool check_wrong_args(char **args)
{
    int x;
    int xx;

    xx = 0;
    while(args[xx])
    {
        x = 0;
        while(args[xx][x])
        {
            if(args[xx][x] == '=')
            {
                printf("unset: %s: invalid parameter name\n", args[xx]);
                return(true);  
            }
            x++;
        }
        xx++;
    }
    return(false);


    
}

void    ft_unset(t_sh *sh, char **args)
{
    int i;
    int j;
    char    **envx;

    i = 0;
    j = 0;
//    while (args[i])
 //       i++;
//    envx = malloc(sizeof(char *) * (i));
    if(check_wrong_args(args) == true)
        return;
    envx = malloc(sizeof(char *) * (sh->vars.envp_total ));
    if(!envx)
        return;
    i = 0;
    // Copia as variáveis de ambiente para 'envx', ignorando aquela especificada em 'args[1]'
    while (sh->envp[i])
    {
        if (ft_strncmp(sh->envp[i], args[1], ft_strlen(args[1])) != 0 || sh->envp[i][ft_strlen(args[1])] != '=')
        {
            envx[j] = ft_strdup(sh->envp[i]);
            j++;
        }
        i++;
    }
    envx[j] = NULL;
    // Atualiza o ponteiro 'envp' com o novo array de variáveis de ambiente, sem a variável removida
	free_env(sh);
    sh->envp = envx;
    sh->vars.envp_total--;
}