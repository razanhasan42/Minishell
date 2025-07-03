/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:04:04 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/23 14:52:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenize_and_prepare(t_tokenize_params *params)
{
	if (!split_into_tokens(params->linked_list, params->command))
		return (0);
	expand_variable(params->linked_list, params->context, *params->env_list);
	assign_token_types(*(params->linked_list));
	return (1);
}

int	build_commands_main(t_command *cmd_list)
{
	t_command	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		build_command_argv(cmd);
		cmd = cmd->next;
	}
	return (1);
}

int	read_and_validate_command(char **command, t_shell_context *context)
{
	*command = readline("minishell> ");
	if (!(*command))
		return (0);
	if (!*(*command))
		return (1);
	add_history(*command);
	if (!check_quotes(*command))
	{
		context->last_exit_status = 2;
		return (-1);
	}
	return (1);
}

static int	process_commands(t_tokenize_params *params, t_command *cmd)
{
	while (cmd)
	{
		parse_heredocs(params, cmd);
		if (*(params->heredoc_cancelled))
		{
			params->context->last_exit_status = 130;
			return (0);
		}
		if (!parse_redirection(cmd->tokens, &cmd->redir_list))
			return (0);
		rm_quote(&cmd->tokens);
		cmd = cmd->next;
	}
	return (1);
}

int	tokenize_and_build_commands(t_tokenize_params *params)
{
	t_command	*cmd;

	if (!tokenize_and_prepare(params))
		return (0);
	*(params->cmd_list) = split_commands_by_pipe(*(params->linked_list));
	if (!*(params->cmd_list))
		return (0);
	cmd = *(params->cmd_list);
	if (!process_commands(params, cmd))
		return (0);
	if (!build_commands_main(*(params->cmd_list)))
		return (0);
	return (1);
}
