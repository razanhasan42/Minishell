/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <rhasan@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:57:46 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/22 13:08:29 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handling_error(t_node *curr)
{
	if (ft_strcmp(curr->next->value, "#") == 0)
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	if (ft_strcmp(curr->next->value, ">") == 0 || ft_strcmp(curr->next->value,
			"<") == 0 || ft_strcmp(curr->next->value, ")") == 0
		|| ft_strcmp(curr->next->value, "(") == 0
		|| ft_strcmp(curr->next->value, "|") == 0
		|| ft_strcmp(curr->next->value, "&") == 0
		|| ft_strcmp(curr->next->value, ";") == 0)
	{
		printf("bash: syntax error near unexpected token %s\n",
			curr->next->value);
		return (1);
	}
	return (0);
}

void	handle_signal_case(int status, t_heredoc_state *state,
		t_shell_context *context)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		context->last_exit_status = 130;
	}
	*(state->heredoc_fd) = -1;
	if (state->heredoc_cancelled)
		*(state->heredoc_cancelled) = 1;
}

void	handle_exit_case(int status, t_heredoc_state *state,
		t_shell_context *context, int read_fd)
{
	int	code;

	*(state->heredoc_fd) = read_fd;
	if (state->heredoc_cancelled)
		*(state->heredoc_cancelled) = 0;
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		if (code == 42)
		{
			context->last_exit_status = 130;
			if (state->heredoc_cancelled)
				*(state->heredoc_cancelled) = 1;
			close(*(state->heredoc_fd));
			*(state->heredoc_fd) = -1;
			return ;
			init_signal();
		}
		context->last_exit_status = code;
	}
}

void	handle_heredoc_parent(pid_t pid, int *pipe_fd, t_heredoc_state *state,
		t_shell_context *context)
{
	int	status;

	signal_parent_heredoc();
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		handle_signal_case(status, state, context);
	else
		handle_exit_case(status, state, context, pipe_fd[0]);
}

void	cleanup_and_exit_hd(t_redirection *hd, t_heredoc_params *params,
		int exit_code, int *pipe_fd)
{
	if (hd->limiter)
		free(hd->limiter);
	free_command_list(params->cmd);
	free_env_list(params->env_list);
	free(hd);
	close(pipe_fd[1]);
	exit(exit_code);
}
