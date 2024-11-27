/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:08:39 by mota              #+#    #+#             */
/*   Updated: 2024/11/27 13:02:08 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//encontra a posição de uma variável no array de ambiente.
/*static int get_var_pos(t_sh *sh, char *var)
{
    int var_len = ft_strchr(var, '=') - var;
    char *var_temp = ft_calloc(var_len + 2, sizeof(char));

    ft_strlcpy(var_temp, var, var_len + 1);
    var_temp[var_len] = '=';

    int var_pos = 0;
    while (sh->envp[var_pos])
    {
        printf("entrou aqui %s\n", sh->envp[var_pos]);
        if (ft_strncmp(sh->envp[var_pos], var_temp, var_len) == 0)
        {
            printf("entrou aqui no if\n");
            free(var_temp);
            return var_pos;
        }
        var_pos++;
    }
    free(var_temp);
    return -1; // Retornar -1 caso não encontre
}*/

//adiciona ou atualiza uma variável de ambiente
static void update_var(t_sh *sh, char *var)
{
    int new_size;
    int i;
    char **envp_temp;

    if (!sh->envp[sh->vars.envp_total])
    {
        new_size = sh->vars.envp_total + 2;
        envp_temp = ft_calloc(new_size, sizeof(char *) + 2);
        i = 0;
        while (i < sh->vars.envp_total)
        {
            envp_temp[i] = ft_strdup(sh->envp[i]);
            i++;
        }
        envp_temp[i] = ft_strdup(var);
        envp_temp[i + 1] = NULL;
        free(sh->envp);
        sh->envp = free_mat(sh->envp);
        sh->envp = envp_temp;
    }
    else
    {
        free(sh->envp[sh->vars.envp_total]);
        sh->envp[sh->vars.envp_total] = ft_strdup(var);
    }
}

// valida se uma string é um identificador de variável apropriado.
static int valid_var(char *var)
{
    int i;

    if (!var || var[0] == '=' || ft_isdigit(var[0]))
        return 0;

    i = 0;
    while (var[i] && var[i] != '=')
    {
        if (var[i] != '_' && !ft_isalnum(var[i]))
            return 0;
        i++;
    }
    return 1;
}

// executa a lógica principal do comando export, 
// permitindo que usuários adicionem ou modifiquem variáveis de ambiente.
void ft_export(t_sh *sh, char **args)
{
    int i;
    
    i = 1;
    while (args[i])
    {
        if (valid_var(args[i]))
        {
            if (ft_strchr(args[i], '='))
            {
                printf("entrou no 2 if\n");
                //var_pos = get_var_pos(sh, args[i]);
                update_var(sh, args[i]);
                printf("entrou no 2 if next up\n");
                sh->error.exit_error = false;
            }
        }
        else
        {
            ft_putstr_fd(": export: ", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd(": not a valid identifier\n", 2);
            sh->error.exit_error = true;
        }
        i++;
    }
    if (!args[1])
        ft_env(sh, args);
}
