/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:46:58 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/23 10:08:01 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	if (n == 0)
		return (0);
	while (s1[counter] == s2[counter] && s1[counter] != '\0')
	{
		if (counter < (n - 1))
			counter++;
		else
			return (0);
	}
	return ((unsigned char)(s1[counter]) - (unsigned char)(s2[counter]));
}
/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while ((s1[counter] != '\0' || s2[counter] != '\0') && counter < n)
	{
		if (s1[counter] < s2[counter])
			return (-1);
		if (s1[counter] > s2[counter])
			return (1);
		counter++;
	}
	return (0);
}
*/
/*
int	main()
{
	char	*t1, *t2;

	t1 = "belele";
	t2 = "belele";
	printf("value is : %d \n", ft_strncmp(t1, t2, 5));
} */
