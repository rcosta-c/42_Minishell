/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:34:20 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/19 10:51:46 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	counter;

	counter = 0;
	while (s[counter] != '\0')
		counter++;
	return (counter);
}
/*
int	main()
{
	char	*x;

	x = "asddasdasdadsd";
	printf(" value : %zu \n", ft_strlen(x));
} */
