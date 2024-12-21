/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mota <mota@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:08:39 by mota              #+#    #+#             */
/*   Updated: 2024/12/21 02:08:07 by mota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static int is_valid_identifier(const char *arg)
{
    int i;

    if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
        return (0);
    i = 0;
    while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static void update_existing_var_concat(char **envp, int pos, const char *arg)
{
    char *new_value;
    char *old_value;
    char *key;
    int key_len;

    key_len = ft_strchr(arg, '+') - arg;
    key = ft_substr(arg, 0, key_len);
    old_value = ft_strchr(envp[pos], '=') + 1;
    new_value = ft_strjoin(old_value, arg + key_len + 2);

    free(envp[pos]);
    envp[pos] = ft_strjoin(key, "=");
    envp[pos] = ft_strjoin(envp[pos], new_value);

    free(new_value);
    free(key);
}

static void update_existing_var(char **envp, int pos, const char *arg)
{
    free(envp[pos]);
    envp[pos] = ft_strdup(arg);
}

static int handle_export_var(t_sh *sh, const char *arg)
{
    char *equal;
    int var_pos;

    if (ft_strchr(arg, '+') && ft_strchr(arg, '+') + 1 == ft_strchr(arg, '='))
    {
        var_pos = get_var_pos(sh, (char *)arg);
        if (var_pos >= 0)
            update_existing_var_concat(sh->envp, var_pos, arg);
        else
            update_var(sh, (char *)arg); // Cria uma nova variável
        return (0);
    }

    equal = ft_strchr(arg, '=');
    if (!equal)
        return (0);

    var_pos = get_var_pos(sh, (char *)arg);
    if (var_pos >= 0)
        update_existing_var(sh->envp, var_pos, arg);
    else
        update_var(sh, (char *)arg);

    return (0);
}

void ft_export(t_sh *sh, char **args)
{
    int i;
    int status;

    status = 0;
    if (!args[1])
    {
        display_exported_vars(sh);
        return;
    }

    i = 1;
    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("`: not a valid identifier\n", 2);
            status = 1;
        }
        else
            handle_export_var(sh, args[i]);
        i++;
    }
    sh->error.exit_error = (status != 0);
}*/

#include "../includes/minishell.h"

// Função para verificar se o identificador é válido
static int is_valid_identifier(const char *arg)
{
    int i;

    if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
        return (0);

    i = 0;
    while (arg[i] && arg[i] != '=' && arg[i] != '+')
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }

    // Permite '+' apenas se for seguido por '='
    if (arg[i] == '+' && arg[i + 1] != '=')
        return (0);

    return (1);
}

static void handle_export_var(t_sh *sh, const char *arg)
{
    char *equal_sign = ft_strchr(arg, '=');
    if (!equal_sign)
        return;

    if (*(equal_sign - 1) == '+') // Case for '+=' operator
    {
        // Get the variable name (without the '+')
        char *var_name = ft_substr(arg, 0, equal_sign - arg - 1);
        char *value_to_add = equal_sign + 1;
        
        // Create the search string with '=' to match environment format
        char *search_var = ft_strjoin(var_name, "=");
        int var_pos = get_var_pos(sh, search_var);
        
        if (var_pos >= 0)
        {
            // Get existing value after the '=' sign
            char *existing_value = ft_strchr(sh->envp[var_pos], '=') + 1;
            
            // Create new combined value
            char *temp_value = ft_strjoin(existing_value, value_to_add);
            
            // Create the complete new variable string
            char *new_var = ft_strjoin(search_var, temp_value);
            
            // Update the environment
            free(sh->envp[var_pos]);
            sh->envp[var_pos] = new_var;
            free(temp_value);
        }
        else 
        {
            // If variable doesn't exist, create it with just the new value
            char *new_var = ft_strjoin(search_var, value_to_add);
            update_var(sh, new_var);
            free(new_var);
        }
        
        free(var_name);
        free(search_var);
    }
    else 
    {
        // Standard case, just update/add the variable
        update_var(sh, (char *)arg);
    }
}

// Função principal para o comando 'export'
void ft_export(t_sh *sh, char **args)
{
    int i;
    int status = 0;

    if (!args[1]) 
    {
        display_exported_vars(sh); // Exibe as variáveis exportadas
        return;
    }

    for (i = 1; args[i]; i++)
    {
        if (!is_valid_identifier(args[i])) // Verifica se o identificador é válido
        {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("`: not a valid identifier\n", 2);
            status = 1;
        }
        else 
        {
            handle_export_var(sh, args[i]); // Trata o export das variáveis
        }
    }

    sh->error.exit_error = (status != 0);
}
