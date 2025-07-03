/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:29:32 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/12 11:15:33 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	size_t	j;
	size_t	i;
	size_t	lsize;

	lsize = ft_strlen(little);
	i = 0;
	j = 0;
	b = (char *)big;
	if (little[j] == '\0')
		return ((char *)b);
	while (i < len && b[i] != '\0')
	{
		j = 0;
		while (little[j] != '\0' && i + j < len && b[i + j] != '\0' && b[i
				+ j] == little[j])
			j++;
		if (j == lsize)
			return (b + i);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
     const char *largestring = "Foo Barr Baz";
     const char *smallstring = "Bar";
     char *p = ft_strnstr(largestring, smallstring, 11);
     printf("%s\n", p);
     printf("%s", ft_strnstr("lorem ipsum dolor sit amet", "dolor", 15));
}*/
