/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:15:16 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/01 12:01:10 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c1;

	c1 = (char)c;
	while (*s != '\0')
	{
		if (*s == c1)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*s == c1)
		return ((char *)s);
	return (NULL);
}
/*
int	main(void)
{
	char	c;
	char	s[15];
	char	*sr;
	char	*a;

	c = '@';
	s[15] = "razan@hasan";
	sr = ft_strchr(s, c);
	a = strchr(s,c);
	printf("%s,%s",a,sr);
	
}
*/
