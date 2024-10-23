/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:17:03 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/22 12:21:03 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		counter;
	const char	*x;

	counter = 0;
	x = (const char *)s;
	while (counter < n)
	{
		if (x[counter] == (char)c)
			return ((void *)x + counter);
		counter++;
	}
	return (NULL);
}
/*
int	main()
{
	const char	teste[] = "012345";
	int	prova;
	size_t	size;
	char	*res;

	size = 6;
	prova = '3';
	res = ft_memchr(teste, prova, size);
	printf("%s\n", res);
}*/
