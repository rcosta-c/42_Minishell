/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 07:11:51 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/22 11:36:24 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	counter;

	counter = 0;
	if (n < 1)
		counter++;
	while (n)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

static long long	abs_val(long long n)
{
	long long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

static char	inverse_cpy(char *numstr, unsigned int nbr, int len)
{
	len--;
	while (len > -1)
	{
		*(numstr + len) = 48 + nbr % 10;
		nbr /= 10;
		len--;
	}
	return (*numstr);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*numstr;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = ft_numlen(n);
	numstr = (char *)malloc(sizeof(char) * len + 1);
	if (!numstr)
		return (NULL);
	*(numstr + len) = '\0';
	nbr = abs_val(n);
	inverse_cpy(numstr, nbr, len);
	if (sign < 0)
		*numstr = 45;
	return (numstr);
}
/*
int	main()
{
	printf("%s\n", ft_itoa(12345));
        printf("%s\n", ft_itoa(-456));
        printf("%s\n", ft_itoa(0));
        printf("%s\n", ft_itoa(2147483647));
        printf("%s\n", ft_itoa(-2147483648));
}*/
