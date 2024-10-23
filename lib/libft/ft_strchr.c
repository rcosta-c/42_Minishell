/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:12:06 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/24 10:34:06 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
		if (!*s++)
			return (0);
	return ((char *)s);
}
/*
int	main()
{
	char	*teste;
	int	prova;

	prova = ' ';
	teste = "bla plab lap";
	printf("value is: %s \n", (ft_strchr(teste, prova)));
        printf("value is: %s \n", (ft_strchr(&teste[4], prova)));

}*/
