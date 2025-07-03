/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulit_in_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:22:04 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/15 12:06:55 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_tokens(t_node *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

static char	**alloc_argv(int count)
{
	char	**argv;

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	argv[count] = NULL;
	return (argv);
}

char	**convert_tokens_to_argv_exec(t_node *tokens)
{
	int		count;
	char	**argv;
	int		i;

	count = count_tokens(tokens);
	argv = alloc_argv(count);
	i = 0;
	if (!argv)
		return (NULL);
	while (tokens)
	{
		argv[i] = ft_strdup(tokens->value);
		if (!argv[i])
		{
			while (i > 0)
				free(argv[--i]);
			free(argv);
			return (NULL);
		}
		i++;
		tokens = tokens->next;
	}
	return (argv);
}

void	unset_env_variable(t_env **env, const char *name)
{
	t_env	*prev;
	t_env	*tmp;

	prev = NULL;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			if (tmp->name)
				free(tmp->name);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_env_variable(env, argv[i]);
		i++;
	}
	return (0);
}
