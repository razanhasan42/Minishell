/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:32 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/02 10:41:35 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		d = (char *)malloc(sizeof(char) * 1);
		if (d)
			d[0] = '\0';
		return (d);
	}
	i = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (d == NULL)
		return (NULL);
	while (len-- && s[start + i] != '\0')
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
/*
int	main(void)
{
	char s[] = "Razan hasan";
	char *d = ft_substr(s, 3, 8);
	printf("%s", d);
}*/
