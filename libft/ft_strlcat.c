/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:22:15 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/01 16:06:30 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s;
	size_t	d;
	size_t	dlen;
	size_t	slen;

	d = 0;
	s = 0;
	i = 0;
	while (dst[d])
		d++;
	dlen = d;
	while (src[s])
		s++;
	slen = s;
	if (size <= d)
		return (size + slen);
	while (src[i] && d + 1 < size)
		dst[d++] = src[i++];
	dst[d] = '\0';
	return (dlen + slen);
}
/*
int	main(void)
{
	char	s[];
	char	d[];

	s[] = "hasan i work";
	d[] = "razan";
	printf("%ld", ft_strlcat(d, s, 9));
}
*/
