/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:02:32 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/05/29 18:34:48 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	add_command_node_safe(t_pipe_vars *vars, t_node *start, t_node *end)
{
	t_command	*cmd;

	cmd = create_command_node(start, end);
	if (!cmd)
		return (false);
	if (!vars->head)
	{
		vars->head = cmd;
		vars->tail = cmd;
	}
	else
	{
		vars->tail->next = cmd;
		vars->tail = cmd;
	}
	return (true);
}

bool	process_pipe_segment(t_pipe_vars *vars)
{
	if (vars->prev)
		vars->prev->next = NULL;
	if (!add_command_node_safe(vars, vars->start, vars->prev))
		return (false);
	vars->start = vars->curr->next;
	return (true);
}

void	init_pipe_split_vars(t_pipe_vars *vars, t_node *tokens)
{
	vars->head = NULL;
	vars->tail = NULL;
	vars->start = tokens;
	vars->curr = tokens;
	vars->prev = NULL;
}
