/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:02:07 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/02 09:45:05 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	i;

	i = ft_strlen(s) + 1;
	dst = (char *)malloc(sizeof(char) * i);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s, i);
	return ((char *)dst);
}
/*
int	main(void)
{
	char	s[];
	char	*dp;

	s[] = "RAZAN HASAN";
	dp = ft_strdup(s);
	printf("%s", dp);
}
*/
