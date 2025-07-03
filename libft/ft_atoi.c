/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:03:28 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/01 13:19:42 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include<stddef.h>
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	ans;

	ans = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		ans = (ans * 10) + (nptr[i++] - '0');
	return (ans * sign);
}
/*
int	main(void)
{
	printf("%d", atoi(" +123"));
	printf("\n%d", ft_atoi("  +123"));
	printf("\n%d", atoi(" +0"));
}
*/
