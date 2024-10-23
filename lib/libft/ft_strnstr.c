/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:07:22 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/04/29 09:25:09 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	cnt1;
	size_t	cnt2;

	if (*little == '\0')
		return ((char *)big);
	cnt1 = 0;
	while (big[cnt1] != '\0' && cnt1 < len)
	{
		cnt2 = 0;
		while (big[cnt1 + cnt2] == little[cnt2] && cnt1 + cnt2 < len)
		{
			if (little[cnt2 + 1] == '\0')
				return ((char *)big + cnt1);
			cnt2++;
		}
		cnt1++;
	}
	return (0);
}
/*
int main(int argc, char **argv)
{
	(void)argc;

	int n = atoi(argv[3]);
	char *res = ft_strnstr(argv[2], argv[1], n);

	printf("Sending argv[1] = \'%s\'\n", argv[1]);
	printf("Sending argv[2] = \'%s\'\n", argv[2]);
	printf("Sending argv[3] = %d\n", n);

	if(!res)
		printf("\'%s\' is not in %d bytes of \'%s\'\n", argv[1], n, argv[2]);
	else
		printf("Found: '%s'\n", res);
}
*/
