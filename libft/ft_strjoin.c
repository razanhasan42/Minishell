/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:00:43 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/02 11:43:47 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;
	int		x;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	new_str = (char *)malloc(i + j + 1);
	if (new_str == NULL)
		return (NULL);
	x = 0;
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		new_str[x++] = s1[i++];
	while (s2[j] != '\0')
		new_str[x++] = s2[j++];
	new_str[x] = '\0';
	return (new_str);
}
/*
int	main(void)
{
	char s1[] = "Razan";
	char s2[] = " hasan";
	char *con = ft_strjoin(s1,s2);
	printf("%s", con);
}*/
