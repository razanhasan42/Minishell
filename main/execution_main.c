/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:56:23 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/23 19:23:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc_fds(t_redirection *list)
{
	while (list)
	{
		if (list->type == REDIR_HEREDOC && list->heredoc_fd != -1)
		{
			close(list->heredoc_fd);
			list->heredoc_fd = -1;
		}
		list = list->next;
	}
}

void	execute_and_cleanup(t_exec_cleanup_params *params,
							t_shell_context *context,
							int *heredoc_cancelled)
{
	int			status;
	t_command	*cmd;

	if (*heredoc_cancelled == 2)
	{
			status = 2;
			*heredoc_cancelled = 0;
	}
	else if (*heredoc_cancelled)
	{
		init_signal();
		status = 130;
		params->heredoc_fd = -1;
		*heredoc_cancelled = 0;
	}
	else
		status = execute_pipeline_main(params->cmd_list, params->env_list,
				context->last_exit_status, params->fds);
	context->last_exit_status = status;
	if (params->command)
		free(params->command);
	cmd = params->cmd_list;
	close_heredoc_fds(params->cmd_list->redir_list);
	while (cmd)
	{
		free_list(&cmd->tokens);
		cmd = cmd->next;
	}
	free_command_list(params->cmd_list);
}

int	is_exit_command(t_command *cmd)
{
	return (cmd && cmd->tokens && cmd->tokens->value
		&& ft_strcmp(cmd->tokens->value, "exit") == 0);
}

static int	handle_single_builtin(t_command *cmd_list, t_env **env_list,
		int exit_status, t_exec_fds *fds)
{
	int	saved_stdout;
	int	saved_stdin;
	int	status;

	status = 0;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (cmd_list->redir_list)
		status = apply_redirections(cmd_list->redir_list, fds);
	remove_redirection_tokens(&cmd_list->tokens);
	if (!status)
		status = exec_builtin_cmd(cmd_list, env_list, exit_status);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	return (status);
}

int	execute_pipeline_main(t_command *cmd_list, t_env **env_list,
		int exit_status, t_exec_fds *fds)
{
	int	status;

	status = 0;
	if (cmd_list && cmd_list->next == NULL && is_builtin(cmd_list))
	{
		if (is_exit_command(cmd_list))
			status = builtin_exit(cmd_list->argv, *env_list, cmd_list,
					exit_status);
		else
			status = handle_single_builtin(cmd_list, env_list, exit_status,
					fds);
	}
	else
	{
		status = excute(cmd_list, *env_list);
	}
	return (status);
}
