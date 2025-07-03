/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:06:52 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/19 12:43:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	setup_fds(t_command *cmd, t_exec_fds *fds)
{
	if (fds->prev_fd != -1)
	{
		if (dup2(fds->prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 prev_fd");
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->next)
	{
		if (dup2(fds->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe write");
			exit(EXIT_FAILURE);
		}
	}
}

static void	close_fds(t_command *cmd, t_exec_fds *fds)
{
	if (fds->prev_fd != -1)
		close(fds->prev_fd);
	if (cmd->next)
	{
		close(fds->pipe_fd[0]);
		close(fds->pipe_fd[1]);
	}
}

void	close_later_heredocs(t_command *current_cmd)
{
	t_command		*cmd;
	t_redirection	*redir;

	cmd = current_cmd->next;
	while (cmd)
	{
		redir = cmd->redir_list;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	setup_child_process(t_command *old_cmd, t_command *cmd, t_exec_fds *fds,
		t_env *env)
{
	reset_signals();
	close_later_heredocs(cmd);
	setup_fds(cmd, fds);
	if (cmd->redir_list)
	{
		if (apply_redirections(cmd->redir_list, fds) != 0)
		{
			free_command_list(old_cmd);
			free_env_list(env);
			exit(1);
		}
	}
	close_fds(cmd, fds);
	remove_redirection_tokens(&cmd->tokens);
	exec_command(cmd->tokens, env, old_cmd, cmd);
	exit(127);
}
