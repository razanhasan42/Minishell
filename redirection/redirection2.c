/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <rhasan@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:03:31 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/22 12:53:06 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_input_redirection(const char *filename, t_exec_fds *fds)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		//safe_close(fds->pipe_fd[0]);
		//safe_close(fds->pipe_fd[1]);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input");
		safe_close(fd);
		safe_close(fds->pipe_fd[0]);
		safe_close(fds->pipe_fd[1]);
		return (1);
	}
	safe_close(fd);
	return (0);
}

static int	handle_output_redirection(const char *filename, t_exec_fds *fds)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		//safe_close(fds->pipe_fd[0]);
		//safe_close(fds->pipe_fd[1]);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		safe_close(fd);
		safe_close(fds->pipe_fd[0]);
		safe_close(fds->pipe_fd[1]);
		return (1);
	}
	safe_close(fd);
	return (0);
}

static int	handle_append_redirection(const char *filename, t_exec_fds *fds)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		//safe_close(fds->pipe_fd[0]);
		//safe_close(fds->pipe_fd[1]);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 append");
		safe_close(fd);
		safe_close(fds->pipe_fd[0]);
		safe_close(fds->pipe_fd[1]);
		return (1);
	}
	safe_close(fd);
	return (0);
}

static int	handle_heredoc_redirection(int heredoc_fd)
{
	if (heredoc_fd != -1)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc_fd");
			close(heredoc_fd);
			heredoc_fd = -1;
			return (1);
		}
		close(heredoc_fd);
		heredoc_fd = -1;
		return (0);
	}
	else
	{
		ft_putstr_fd("Error: heredoc_fd not set\n", 2);
		return (1);
	}
}

int	apply_redirections(t_redirection *redir_list, t_exec_fds *fds)
{
	t_redirection	*curr;
	int				status;

	curr = redir_list;
	while (curr)
	{
		status = 0;
		if (curr->type == REDIR_HEREDOC)
			status = handle_heredoc_redirection(curr->heredoc_fd);
		else if (curr->type == REDIR_INPUT)
			status = handle_input_redirection(curr->filename, fds);
		else if (curr->type == REDIR_OUTPUT)
			status = handle_output_redirection(curr->filename, fds);
		else if (curr->type == REDIR_APPEND)
			status = handle_append_redirection(curr->filename, fds);
		if (status)
			return (1);
		curr = curr->next;
	}
	return (0);
}
