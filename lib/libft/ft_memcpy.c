/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:19:51 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/22 14:21:32 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	ft_memmove(dest, src, n);
	return (dest);
}
/*
int     main()
{
        int     ch, count;
        char    *let = "teste";
        char    *des;

        write(1, let, sizeof(char) * 4);
        write(1, "-1-\n", 4);
        ft_memcpy(des, let, 4);
        write(1, des, sizeof(char) * 4);
        write(1, "-2-\n", 4);
        return(0);
}*/
