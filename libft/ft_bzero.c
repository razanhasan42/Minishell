/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:45:44 by rhasan            #+#    #+#             */
/*   Updated: 2024/08/28 16:17:16 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		*str++ = 0;
	}
}
/*
#include <stddef.h>

int	main(void)
{
	char s[5] = "RAZAN";
	ft_bzero(s, 3);
	printf("%s", s);
}*/
