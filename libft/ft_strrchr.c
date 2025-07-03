/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:52:53 by rhasan            #+#    #+#             */
/*   Updated: 2024/08/29 13:08:39 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;
	char		c1;

	last = NULL;
	c1 = (char)c;
	while (*s != '\0')
	{
		if (*s == c1)
		{
			last = s;
		}
		s++;
	}
	if (c1 == '\0')
		return ((char *)s);
	return ((char *)last);
}
/*
int	main(void)
{
	char c = '\0';
	char s[15] = "Razan@ha@sn";
	char *sr = ft_strrchr(s, c);
	printf("%s", sr);
}*/
