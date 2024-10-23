/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:19:55 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/22 12:11:25 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int	main()
{
	int	count;
        char    let[] = "rstu";

	count = 0;
        write(1, let, sizeof(char) * 4);
        write(1, "-1-\n", 4);
	ft_bzero(&let, 3);
        write(1, let, sizeof(char) * 4);
        write(1, "-2-\n", 4);
        return(0);
}*/
