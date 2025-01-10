/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:18:39 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/10 17:21:57 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_token_seeker3(t_sh *sh, int n, int *x)
{
    char	b[2500];
    int		bx;
    char	*c;
    bool	in_quotes;

    in_quotes = false;
    c = ft_strdup(sh->tokens[n].tokens);
    while (sh->tokens[n].tokens[*x])
    {
        if (sh->tokens[n].tokens[*x] == '\'')
        {
            in_quotes = !in_quotes;
            (*x)++;
            continue;
        }
        if (!in_quotes && sh->tokens[n].tokens[*x] == '$')
        {
            bx = 0;
            (*x)++;
            while (sh->tokens[n].tokens[*x] 
                   && sh->tokens[n].tokens[*x] != '=' 
                   && sh->tokens[n].tokens[*x] != '\'')
            {
                b[bx++] = sh->tokens[n].tokens[(*x)++];
            }
            b[bx] = '\0';
            free(c);
            c = search_envp(sh, b);
            if (!c)
            {
                c = ft_strdup(" ");
                sh->tokens[n].exp_empty = true;
            }
        }
        else
            (*x)++;
    }
    return (c);
}