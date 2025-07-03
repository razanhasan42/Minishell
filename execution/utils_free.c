/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:43:03 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/12 11:47:41 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**env_to_envp(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**envp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	count = 0;
	while (tmp)
	{
		envp[count] = ft_strjoin_3(tmp->name, "=", tmp->value);
		count++;
		tmp = tmp->next;
	}
	envp[count] = NULL;
	return (envp);
}

void	free_token_node(t_node *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	free(node);
}

static void	remove_redir_pair(t_node **tokens, t_node *prev, t_node *curr)
{
	t_node	*tmp;

	tmp = curr->next;
	if (prev)
	{
		if (tmp && tmp->next)
			prev->next = tmp->next;
		else
			prev->next = NULL;
	}
	else
	{
		if (tmp && tmp->next)
			*tokens = tmp->next;
		else
			*tokens = NULL;
	}
	free_token_node(curr);
	if (tmp)
		free_token_node(tmp);
}

void	remove_redirection_tokens(t_node **tokens)
{
	t_node	*curr;
	t_node	*prev;
	t_node	*next;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (curr->type == REDIR_INPUT || curr->type == REDIR_OUTPUT
			|| curr->type == REDIR_APPEND || curr->type == REDIR_HEREDOC)
		{
			if (curr->next && curr->next->next)
				next = curr->next->next;
			else
				next = NULL;
			remove_redir_pair(tokens, prev, curr);
			curr = next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
