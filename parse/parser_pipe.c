/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:29:16 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/14 19:26:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	duplicate_word_to_argv(char **argv, char *value, int index)
{
	argv[index] = ft_strdup(value);
	if (!argv[index])
	{
		printf("ERROR: Memory allocation failed for %s.\n", value);
		return (0);
	}
	return (1);
}

static void	free_argv_on_failure(char **argv, int last_index)
{
	while (--last_index >= 0)
		free(argv[last_index]);
	free(argv);
}

t_node	*skip_if_redirection(t_node *node)
{
	if ((node->type == REDIR_INPUT || node->type == REDIR_OUTPUT
			|| node->type == REDIR_APPEND || node->type == REDIR_HEREDOC))
	{
		if (node->next)
			return (node->next->next);
		else
			return (NULL);
	}
	return (node->next);
}

int	process_word_token(t_command *cmd, t_node *curr, int *i)
{
	if (!duplicate_word_to_argv(cmd->argv, curr->value, *i))
	{
		free_argv_on_failure(cmd->argv, *i);
		cmd->argv = NULL;
		return (0);
	}
	(*i)++;
	return (1);
}

void	build_command_argv(t_command *cmd)
{
	int	count;

	count = count_words(cmd->tokens);
	if (!allocate_argv(cmd, count))
		return ;
	if (!fill_argv(cmd, count))
	{
		ft_putstr_fd("ERROR: fill_argv failed\n", 2);
		free(cmd->argv);
		cmd->argv = NULL;
	}
}
