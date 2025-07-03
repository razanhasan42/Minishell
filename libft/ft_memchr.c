/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:07:33 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/01 11:59:31 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c1;
	unsigned char	*test;

	test = (unsigned char *)s;
	c1 = (unsigned char)c;
	while (n && *test != c1)
	{
		++test;
		--n;
	}
	if (n)
		return ((void *)test);
	else
		return (NULL);
}
/*
int	main(void)
{
	//char c = '\0';
	//char s[15] = "razan@hasan";
	char *sr = ft_memchr("bonjourno", 'n', 2);
	//char *a = memchr(s, c, 11);
	printf("%s", sr);
	
}*/
