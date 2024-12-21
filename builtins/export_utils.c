/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:26:43 by mota              #+#    #+#             */
/*   Updated: 2024/12/21 02:08:34 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int get_var_pos(t_sh *sh, char *var)
{
    int i;
    int len;

    i = 0;
    len = ft_strchr(var, '=') - var;
    if (len <= 0)
        return (-1);
    while (i < sh->vars.envp_total)
    {
        if (!ft_strncmp(sh->envp[i], var, len) && sh->envp[i][len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

void update_var(t_sh *sh, char *var)
{
    int var_pos;
    int i;
    int new_size;
    char **envp_temp;

    var_pos = get_var_pos(sh, var);
    if (var_pos >= 0)
    {
        free(sh->envp[var_pos]);
        sh->envp[var_pos] = ft_strdup(var);
        return;
    }
    new_size = sh->vars.envp_total + 2;
    envp_temp = ft_calloc(new_size, sizeof(char *));
    if (!envp_temp)
        exit(EXIT_FAILURE);
    i = 0;
    while (i < sh->vars.envp_total)
    {
        envp_temp[i] = ft_strdup(sh->envp[i]);
        if (!envp_temp[i])
            exit(EXIT_FAILURE);
        i++;
    }
    envp_temp[i] = ft_strdup(var);
    if (!envp_temp[i])
        exit(EXIT_FAILURE);
    sh->vars.envp_total++;
    free_env(sh);
    sh->envp = envp_temp;
}*/

void display_exported_vars(t_sh *sh)
{
    int i = 0;

    while (sh->envp[i])
    {
        char *equal_sign = ft_strchr(sh->envp[i], '=');
        if (equal_sign)
        {
            // Print variable name
            ft_putstr_fd("declare -x ", 1);
            write(1, sh->envp[i], equal_sign - sh->envp[i] + 1);
            
            // Print value in quotes
            ft_putchar_fd('"', 1);
            ft_putstr_fd(equal_sign + 1, 1);
            ft_putchar_fd('"', 1);
            ft_putchar_fd('\n', 1);
        }
        else
        {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(sh->envp[i], 1);
            ft_putchar_fd('\n', 1);
        }
        i++;
    }
    sh->error.exit_error = false;
}

// Função para encontrar a posição de uma variável no ambiente
int get_var_pos(t_sh *sh, char *var)
{
    int i;
    int len;

    i = 0;
    len = ft_strchr(var, '=') - var;
    if (len <= 0)
        return (-1);

    while (i < sh->vars.envp_total)
    {
        if (!ft_strncmp(sh->envp[i], var, len) && sh->envp[i][len] == '=')
            return (i);
        i++;
    }

    return (-1);
}

void update_var(t_sh *sh, char *var)
{
    int var_pos;
    int i;
    int new_size;
    char **envp_temp;

    var_pos = get_var_pos(sh, var);
    if (var_pos >= 0) // Se a variável já existir
    {
        free(sh->envp[var_pos]);
        sh->envp[var_pos] = ft_strdup(var); // Atualiza com o novo valor
        return;
    }

    // Se a variável não existir, adiciona uma nova no ambiente
    new_size = sh->vars.envp_total + 2;
    envp_temp = ft_calloc(new_size, sizeof(char *));
    if (!envp_temp)
        exit(EXIT_FAILURE);

    i = 0;
    while (i < sh->vars.envp_total)
    {
        envp_temp[i] = ft_strdup(sh->envp[i]);
        if (!envp_temp[i])
            exit(EXIT_FAILURE);
        i++;
    }

    envp_temp[i] = ft_strdup(var);
    if (!envp_temp[i])
        exit(EXIT_FAILURE);

    sh->vars.envp_total++;
    free_env(sh);
    sh->envp = envp_temp;
}
