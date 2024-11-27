/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:08:39 by mota              #+#    #+#             */
/*   Updated: 2024/11/27 16:24:47 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Retorna a posição de uma variável no envp, ou -1 se não encontrada
static int get_var_pos(t_sh *sh, char *var)
{
    int i;
    int len;

    len = ft_strchr(var, '=') - var;
    if (len <= 0)
        return -1;

    for (i = 0; i < sh->vars.envp_total; i++)
    {
        if (!ft_strncmp(sh->envp[i], var, len) && sh->envp[i][len] == '=')
            return i;
    }
    return -1;
}
// Adiciona ou atualiza uma variável de ambiente
static void update_var(t_sh *sh, char *var)
{
    int var_pos;
    int i;
    char **envp_temp;

    // Verifica se a variável já existe no envp
    var_pos = get_var_pos(sh, var);
    if (var_pos >= 0)
    {
        // Atualiza a variável existente
        free(sh->envp[var_pos]);
        sh->envp[var_pos] = ft_strdup(var);
        return;
    }
    // Calcula o novo tamanho da matriz envp
    int new_size = sh->vars.envp_total + 2; // +1 para a nova variável, +1 para NULL
    // Aloca memória para a nova matriz envp
    envp_temp = ft_calloc(new_size, sizeof(char *));
    if (!envp_temp)
    {
        free(envp_temp);
        exit(EXIT_FAILURE);
    }
    // Copia as variáveis existentes para a nova matriz
    i = 0;
    while (i < sh->vars.envp_total)
    {
        envp_temp[i] = ft_strdup(sh->envp[i]);
        if (!envp_temp[i])
        {
            free(envp_temp);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    // Adiciona a nova variável
    envp_temp[i] = ft_strdup(var);
    if (!envp_temp[i])
    {
        free(envp_temp);
        exit(EXIT_FAILURE);
    }
    // Atualiza o total de variáveis
    sh->vars.envp_total++;
    // Substitui a matriz envp antiga pela nova
    free(sh->envp);
    sh->envp = envp_temp;
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
                update_var(sh, args[i]);
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
