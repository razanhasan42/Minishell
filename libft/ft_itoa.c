/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:48:23 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/08 12:11:56 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fun(long i, int len, char *str)
{
	int	isneg;

	isneg = 0;
	if (i < 0)
	{
		i *= -1;
		isneg = 1;
		str[0] = '-';
	}
	str[len--] = '\0';
	while (len >= isneg)
	{
		str[len--] = (i % 10) + '0';
		i /= 10;
	}
	return (str);
}

static int	ft_intlen(long i)
{
	int	len;

	len = 0;
	if (i == 0)
		len = 1;
	else if (i < 0)
	{
		len++;
		i *= -1;
	}
	while (i > 0)
	{
		len++;
		i /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	i;
	int		len;

	i = n;
	len = ft_intlen(i);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (i == 0)
	{
		str[len--] = '\0';
		str[len--] = i + '0';
	}
	else
		ft_fun(i, len, str);
	return (str);
}
/*
int	main(void)
{

	printf("%s" , ft_itoa(0));
}*/
