/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:44:46 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/23 07:52:52 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				x;

	x = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (!src && !dest)
		return (0);
	if (s < d)
	{
		x = n;
		while (x-- > 0)
			d[x] = s[x];
	}
	else
	{
		while (x < n)
		{
			d[x] = s[x];
			x++;
		}
	}
	return (dest);
}
/*
int	main()
{
	int	ch, count;
        char    *let = "teste";
	char	*des;

        write(1, let, sizeof(char) * 4);
        write(1, "-1-\n", 4);
	ft_memmove(des, let, 3);
        write(1, des, sizeof(char) * 4);
        write(1, "-2-\n", 4);
        return(0);
}*/
