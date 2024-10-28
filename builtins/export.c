/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:08:39 by mota              #+#    #+#             */
/*   Updated: 2024/10/28 20:43:13 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//encontra a posição de uma variável no array de ambiente.
static int  get_var_pos(char *var, char **envp)
{
    int var_len = ft_strchr(var, '=') - var;
    char *var_temp = ft_calloc(var_len + 2, sizeof(char));

    ft_strlcpy(var_temp, var, var_len + 1);
    var_temp[var_len] = '=';
    
    for (int var_pos = 0; envp[var_pos]; var_pos++)
    {
        if (ft_strncmp(envp[var_pos], var_temp, var_len + 1) == 0)
        {
            free(var_temp);
            return var_pos;
        }
    }
    free_ptr(var_temp);
    return -1; // Retornar -1 caso não encontre
}

//adiciona ou atualiza uma variável de ambiente
static void update_var(char *var, int var_pos, char ***envp)
{
    if (!envp[0][var_pos])
    {
        int new_size = var_pos + 2;
        char **envp_temp = ft_calloc(new_size, sizeof(char *));
        for (int i = 0; i < var_pos; i++)
            envp_temp[i] = ft_strdup(envp[0][i]);
        envp_temp[var_pos] = ft_strdup(var);
        
        *envp = free_mat(*envp);
        *envp = envp_temp;
    }
    else
    {
        free_ptr(envp[0][var_pos]);
        envp[0][var_pos] = ft_strdup(var);
    }
}

// valida se uma string é um identificador de variável apropriado.
static int  valid_var(char *var)
{
    if (!var || var[0] == '=' || ft_isdigit(var[0]))
        return 0;

    for (int i = 0; var[i] && var[i] != '='; i++)
    {
        if (var[i] != '_' && !ft_isalnum(var[i]))
            return 0;
    }
    return 1;
}

// executa a lógica principal do comando export, 
// permitindo que usuários adicionem ou modifiquem variáveis de ambiente.
void    ft_export(t_sh *sh, char **cmd, char ***envp)
{
    for (int i = 1; cmd[i]; i++)
    {
        if (valid_var(cmd[i]))
        {
            if (ft_strchr(cmd[i], '='))
            {
                int var_pos = get_var_pos(cmd[i], *envp);
                update_var(cmd[i], var_pos, envp);
                 sh->error.exit_error = false;
            }
        }
        else
        {
            ft_putstr_fd(": export: ", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putstr_fd(": not a valid identifier\n", 2);
             sh->error.exit_error = true;
        }
    }

    if (!cmd[1])
        ft_env(sh, cmd, envp);
}
