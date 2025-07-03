/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:02:30 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/23 14:45:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_heredoc(t_redirection *hd, t_heredoc_params *params,
		t_command *cmd_list)
{
	int				pipe_fd[2];
	pid_t			pid;
	t_heredoc_state	state;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		return (handle_heredoc_child(hd, params, pipe_fd, cmd_list), 1);
	else
	{
		state.heredoc_fd = &(hd->heredoc_fd);
		state.heredoc_cancelled = params->state->heredoc_cancelled;
		handle_heredoc_parent(pid, pipe_fd, &state, params->context);
	}
	return (0);
}

void	init_heredoc_limiter(t_redirection *hd, char *lim)
{
	if (lim[0] == '\'' || lim[0] == '\"')
	{
		hd->is_quoted_limiter = 1;
		hd->limiter = strip_quotes(lim);
	}
	else
	{
		hd->is_quoted_limiter = 0;
		hd->limiter = ft_strdup(lim);
	}
}

int	handle_heredoc_allocation_failure(t_heredoc_state *state)
{
	*(state->heredoc_fd) = -1;
	*(state->heredoc_cancelled) = 2;
	return (0);
}

int	handle_heredoc_final(t_redirection *hd, t_heredoc_state *state)
{
	if (hd->heredoc_fd == -1)
	{
		if (hd->limiter)
			free(hd->limiter);
		free(hd);
		*(state->heredoc_fd) = -1;
		*(state->heredoc_cancelled) = 1;
		return (0);
	}
	*(state->heredoc_fd) = hd->heredoc_fd;
	if (hd->limiter)
		free(hd->limiter);
	free(hd);
	return (1);
}
