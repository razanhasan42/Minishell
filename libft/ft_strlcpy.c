/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:46:09 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/01 14:53:20 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = 0;
	while (src[s] != '\0')
		s++;
	if (size == 0)
		return (s);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s);
}
/*
int	main(void)
{
	char d[] = "1 0 4,5";
	//char *s = "a 2 0 5";

	printf("%ld", ft_strlcpy(d, "1,2,3,0,4", 9));
	printf("%s",  d);
	
}*/
