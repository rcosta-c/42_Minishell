/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:26:01 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/10/28 09:40:09 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*x;

	x = NULL;
	while (*s)
	{
		if (*s == (char)c)
			x = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (x);
}
/*
#include <stdio.h>

int	main()
{
	char	*teste;
	int	prova;

	prova = '=';
	teste = "USER=blaplabrpla";
	printf("value is: %s \n", ft_strrchr(teste, prova));
}*/
