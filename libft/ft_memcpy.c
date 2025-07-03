/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:26:27 by rhasan            #+#    #+#             */
/*   Updated: 2024/08/28 16:01:03 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*sr;
	unsigned char	*ds;

	sr = (unsigned char *)src;
	ds = (unsigned char *)dest;
	if (!ds && !sr)
		return (NULL);
	while (n > 0)
	{
		*ds = *sr;
		ds++;
		sr++;
		n--;
	}
	return (dest);
}
/*
int	main(void)
{
	char src[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char dest[6];

	ft_memcpy(dest, src, 6);
	//dest[5] = '\0';
	dest[6] = '\0';
	printf("%s", dest);
}*/
