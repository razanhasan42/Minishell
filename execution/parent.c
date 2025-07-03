/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:10:02 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/15 12:34:00 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_heredocs(t_command *cmd)
{
	t_redirection	*redir;

	if (!cmd || !cmd->redir_list)
		return ;
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
}

static void	update_pipe_fds(t_exec_fds *fds, t_command *cmd)
{
	if (fds->pipe_fd[1] != -1)
		close(fds->pipe_fd[1]);
	if (fds->prev_fd != -1)
		close(fds->prev_fd);
	if (cmd->next)
		fds->prev_fd = fds->pipe_fd[0];
	else
	{
		if (fds->pipe_fd[0] != -1)
			close(fds->pipe_fd[0]);
		fds->prev_fd = -1;
	}
}

void	handle_parent_cleanup(t_exec_fds *fds, t_command *cmd)
{
	if (!cmd)
	{
		ft_putstr_fd("cmd is NULL\n", 2);
		return ;
	}
	close_heredocs(cmd);
	update_pipe_fds(fds, cmd);
}
