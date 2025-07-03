/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:55 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/17 12:53:42 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(t_node *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == WORD)
			count++;
		else if (tokens->type == REDIR_INPUT || tokens->type == REDIR_OUTPUT
			|| tokens->type == REDIR_APPEND
			|| tokens->type == REDIR_HEREDOC)
		{
			if (tokens->next)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (count);
}

void	mark_pipe_tokens(t_node *tokens)
{
	while (tokens)
	{
		if (tokens->value && ft_strcmp(tokens->value, "|") == 0)
			tokens->type = TOKEN_PIPE;
		tokens = tokens->next;
	}
}

t_node	*skip_non_word_tokens(t_node *curr)
{
	if (curr->type == TOKEN_PIPE)
		return (curr->next);
	else
		return (skip_if_redirection(curr));
}

t_command	*create_command_node(t_node *start, t_node *end)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->tokens = start;
	node->next = NULL;
	node->argv = NULL;
	node->redir_list = NULL;
	node->type = WORD;
	if (end)
		end->next = NULL;
	return (node);
}
