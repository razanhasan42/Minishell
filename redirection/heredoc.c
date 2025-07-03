/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:04:55 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/23 14:29:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_parse_heredoc(t_node *curr, t_heredoc_params *params,
		t_command *cmd_list)
{
	t_redirection	*hd;

	if (handling_error(curr))
		return (handle_heredoc_allocation_failure(params->state));
	hd = malloc(sizeof(t_redirection));
	if (!hd)
		exit(1);
	init_heredoc_limiter(hd, curr->next->value);
	if (process_heredoc(hd, params, cmd_list))
		return (2);
	return (handle_heredoc_final(hd, params->state));
}

static int	handle_parse_result(int ret, t_tokenize_params *params)
{
	if (ret == 2)
	{
		free_command_list(*(params->cmd_list));
		free_env_list(*(params->env_list));
		exit(130);
	}
	else if (!ret)
		return (1);
	return (0);
}

static int	create_and_append_redirection(t_command *cmd, char *value,
		int heredoc_fd)
{
	t_redirection	*redir;

	redir = new_redirection(REDIR_HEREDOC, value);
	if (!redir)
	{
		if (heredoc_fd != -1)
			close(heredoc_fd);
		return (0);
	}
	redir->heredoc_fd = heredoc_fd;
	if (!cmd->redir_list)
		cmd->redir_list = redir;
	else
		append_redir(cmd->redir_list, redir);
	return (1);
}

static int	handle_heredoc_node(t_node *curr, t_tokenize_params *params,
		t_command *cmd, t_heredoc_state *state)
{
	int					ret;
	t_heredoc_params	h_params;

	if (*(state->heredoc_fd) != -1)
		free_redirections(&cmd->redir_list);
	if (!curr->next || !curr->next->value)
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		return (0);
	}
	h_params.env_list = *(params->env_list);
	h_params.context = params->context;
	h_params.cmd = cmd;
	h_params.state = state;
	ret = handle_parse_heredoc(curr, &h_params, *(params->cmd_list));
	if (handle_parse_result(ret, params))
		return (0);
	if (!create_and_append_redirection(cmd, curr->next->value,
			*(state->heredoc_fd)))
		return (0);
	return (1);
}

int	parse_heredocs(t_tokenize_params *params, t_command *cmd)
{
	t_node			*curr;
	int				heredoc_fd;
	t_heredoc_state	state;

	curr = cmd->tokens;
	heredoc_fd = -1;
	state.heredoc_fd = &heredoc_fd;
	state.heredoc_cancelled = params->heredoc_cancelled;
	g_signal_status = 0;
	while (curr)
	{
		if (curr->type == REDIR_HEREDOC)
		{
			if (!handle_heredoc_node(curr, params, cmd, &state))
				return (0);
			if (*(state.heredoc_cancelled))
			{
				params->context->last_exit_status = 130;
				return (0);
			}
		}
		curr = curr->next;
	}
	init_signal();
	return (1);
}
