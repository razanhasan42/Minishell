/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:21:34 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/12 12:47:27 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_pipe_split(t_pipe_vars *vars)
{
	t_node	*pipe_node;
	t_node	*next_segment;

	pipe_node = vars->curr;
	next_segment = pipe_node->next;
	if (vars->prev)
		vars->prev->next = NULL;
	if (!add_command_node_safe(vars, vars->start, vars->prev))
		return (0);
	if (pipe_node->value)
		free(pipe_node->value);
	free(pipe_node);
	vars->start = next_segment;
	vars->curr = next_segment;
	vars->prev = NULL;
	return (1);
}

t_command	*split_commands_by_pipe(t_node *tokens)
{
	t_pipe_vars	vars;

	init_pipe_split_vars(&vars, tokens);
	while (vars.curr)
	{
		if (vars.curr->type == TOKEN_PIPE)
		{
			if (!handle_pipe_split(&vars))
				return (NULL);
			continue ;
		}
		vars.prev = vars.curr;
		vars.curr = vars.curr->next;
	}
	if (vars.start)
	{
		if (!add_command_node_safe(&vars, vars.start, vars.prev))
			return (NULL);
	}
	return (vars.head);
}

int	has_non_redirection_token(t_node *tok)
{
	while (tok)
	{
		if (tok->type == WORD || tok->type == TOKEN_PIPE
			|| tok->type == REDIR_HEREDOC)
			return (1);
		tok = tok->next;
	}
	return (0);
}

int	allocate_argv(t_command *cmd, int count)
{
	cmd->argv = malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
	{
		ft_putstr_fd("ERROR: Memory allocation failed for argv.\n", 2);
		return (0);
	}
	return (1);
}

int	fill_argv(t_command *cmd, int count)
{
	t_node	*curr;
	int		i;

	curr = cmd->tokens;
	i = 0;
	while (curr)
	{
		if (curr->type == WORD)
		{
			if (!process_word_token(cmd, curr, &i))
				return (0);
			curr = curr->next;
		}
		else
			curr = skip_non_word_tokens(curr);
	}
	cmd->argv[count] = NULL;
	return (1);
}
