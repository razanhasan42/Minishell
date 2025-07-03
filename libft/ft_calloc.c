/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:44:04 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/02 08:58:17 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, (size * nmemb));
	return (p);
}
/*
int	main(void)
{
	int *p = (int *)ft_calloc(4, sizeof(int));
	if (p == NULL)
		printf("memory not allocated\n");
	else
	{
		int i = 0;
		while (i < 4)
		{
		
			printf("%d\n", p[i]);
			i++;
		}
	}	
}*/
