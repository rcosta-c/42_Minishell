/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:26:01 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/23 11:05:18 by rcosta-c         ###   ########.fr       */
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
int	main()
{
	char	*teste;
	int	prova;

	prova = 'l';
	teste = "blaplabrpla";
	printf("value is: %s \n", ft_strrchr(teste, prova));
} */
