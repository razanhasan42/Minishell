/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:53:41 by rhasan            #+#    #+#             */
/*   Updated: 2024/09/11 15:54:59 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(char const *s, char c)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!flag)
			{
				len++;
				flag = 1;
			}
		}
		else
			flag = 0;
		s++;
	}
	return (len);
}

static int	ft_slen(char const *s, char c, int j)
{
	int	len;

	len = 0;
	while (s[j] && s[j] != c)
	{
		len++;
		j++;
	}
	return (len);
}

static char	*ft_fun(char const *s, char c, int *j)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_slen(s, c, *j);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
		str[i++] = s[(*j)++];
	str[len] = '\0';
	return (str);
}

static int	check_malloc(char **s, int i)
{
	if (!s[i])
	{
		while (i-- > 0)
			free(s[i]);
		free(s);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		j;
	int		i;
	int		len;

	i = 0;
	j = 0;
	len = ft_wcount(s, c);
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		while (s[j] == c)
			j++;
		if (s[j] != '\0')
		{
			str[i++] = ft_fun(s, c, &j);
			if (!check_malloc(str, i - 1))
				return (NULL);
		}
	}
	str[len] = NULL;
	return (str);
}
/*
int	main(void) {
	char test_case[] = "      Leadingp and trailing    spaces";
	char delimiter = ' ';

	char **str = ft_split(test_case, delimiter);

	int i = 0;
	while (str[i]) {
		printf("%s\n", str[i]);
		i++;
	}
	free(str);

	return (0);
}*/
