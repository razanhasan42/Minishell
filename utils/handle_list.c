/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:30:35 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/19 16:10:28 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_node **node)
{
	t_node	*curr;

	if (!node || !(*node))
		return ;
	while (*node)
	{
		curr = *node;
		*node = (*node)->next;
		if (curr->value)
			free(curr->value);
		free(curr);
	}
	*node = NULL;
}

static t_node	*create_new_node(char *token)
{
	t_node	*newnode;

	newnode = (t_node *)malloc(sizeof(t_node));
	if (!newnode)
		return (NULL);
	newnode->value = ft_strdup(token);
	if (!newnode->value)
	{
		free(newnode);
		return (NULL);
	}
	newnode->next = NULL;
	newnode->type = -1;
	return (newnode);
}

void	add_node_to_list(t_node **node, char *token)
{
	t_node	*newnode;
	t_node	*curr;

	if (!node || !token)
		return ;
	newnode = create_new_node(token);
	if (!newnode)
	{
		free_list(node);
		exit(EXIT_FAILURE);
	}
	if (!*node)
		*node = newnode;
	else
	{
		curr = *node;
		while (curr->next)
			curr = curr->next;
		curr->next = newnode;
	}
}

void	print_split_result(t_node *head)
{
	while (head)
	{
		printf("%s\n", head->value);
		head = head->next;
	}
}
