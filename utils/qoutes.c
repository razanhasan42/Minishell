/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:38:59 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/12 16:41:25 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_qoutes(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	check_quotes(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
			{
				printf("Error: Missing closing quote for %c\n", quote);
				return (0);
			}
		}
		if (str[i])
			i++;
	}
	return (1);
}

char	*strip_quotes(char *value)
{
	size_t	len;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
		return (ft_substr(value, 1, len - 2));
	return (ft_strdup(value));
}

static char	*remove_q(char *str)
{
	int		i;
	char	start;
	char	*tmp;
	int		j;

	j = 0;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (str[i] != '\'' && str[i] != '"' && str[i])
			tmp[j++] = str[i++];
		if (!str[i])
			break ;
		start = str[i++];
		while (str[i] && str[i] != start)
			tmp[j++] = str[i++];
		if (str[i] == start)
			i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	rm_quote(t_node **node)
{
	t_node	*curr;
	char	*new_value;

	curr = *node;
	while (curr)
	{
		if (check_quotes(curr->value) == 1)
		{
			new_value = remove_q(curr->value);
			if (new_value)
			{
				free(curr->value);
				curr->value = new_value;
			}
		}
		curr = curr->next;
	}
}
