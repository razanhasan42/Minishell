/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_heredoc_fun.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:19:01 by marvin            #+#    #+#             */
/*   Updated: 2025/06/19 16:15:52 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_and_check_heredoc_line(t_redirection *hd, t_env *env_list)
{
	char	*line;
	char	*expanded;

	line = readline("> ");
	if (!line)
		return (NULL);
	if (ft_strcmp(hd->limiter, "`") == 0)
	{
		free(line);
		return ((char *)1);
	}
	if (ft_strcmp(line, hd->limiter) == 0)
	{
		free(line);
		return (NULL);
	}
	if (hd->is_quoted_limiter == 0)
	{
		expanded = expand_line_with_vars(line, env_list);
		free(line);
		line = expanded;
	}
	return (line);
}

static void	write_heredoc_line(char *line, int write_fd)
{
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
}

static int	process_heredoc_line(t_redirection *hd, t_env *env_list,
		int write_fd)
{
	char	*line;

	line = read_and_check_heredoc_line(hd, env_list);
	if (!line)
		return (0);
	if (line == (char *)1)
		return (1);
	write_heredoc_line(line, write_fd);
	return (1);
}

void	close_all_heredocs_except(t_command *cmd_list, t_command *current_cmd)
{
	t_redirection	*redir;

	while (cmd_list)
	{
		if (cmd_list != current_cmd)
		{
			redir = cmd_list->redir_list;
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
		cmd_list = cmd_list->next;
	}
}

void	handle_heredoc_child(t_redirection *hd, t_heredoc_params *params,
		int *pipe_fd, t_command *cmd_list)
{
	signal_child_heredoc();
	close_all_heredocs_except(cmd_list, params->cmd);
	close(pipe_fd[0]);
	while (process_heredoc_line(hd, params->env_list, pipe_fd[1]))
		;
	free_list(&cmd_list->tokens);
	free_redirections(&cmd_list->redir_list);
	if (g_signal_status == SIGINT)
		cleanup_and_exit_hd(hd, params, 42, pipe_fd);
	cleanup_and_exit_hd(hd, params, 0, pipe_fd);
}
