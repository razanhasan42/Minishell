/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirction_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:10:05 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/18 12:40:27 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_redir_type(t_node *curr)
{
	if (ft_strcmp(curr->value, "<") == 0)
		curr->type = REDIR_INPUT;
	else if (ft_strcmp(curr->value, ">") == 0)
		curr->type = REDIR_OUTPUT;
	else if (ft_strcmp(curr->value, ">>") == 0)
		curr->type = REDIR_APPEND;
	else if (ft_strcmp(curr->value, "<<") == 0)
		curr->type = REDIR_HEREDOC;
}

void	free_redirections(t_redirection **redir)
{
	t_redirection	*tmp;

	if (!redir || !*redir)
		return ;
	while (*redir)
	{
		tmp = (*redir)->next;
		if ((*redir)->type == REDIR_HEREDOC && (*redir)->heredoc_fd != -1)
			close((*redir)->heredoc_fd);
		if ((*redir)->filename)
			free((*redir)->filename);
		if ((*redir)->limiter)
			free((*redir)->limiter);
		free(*redir);
		*redir = tmp;
	}
	*redir = NULL;
}

void	safe_close(int fd)
{
	if (fd >= 0 && fd > 2)
		close(fd);
}

t_redirection	*new_redirection(t_token_type type, const char *limiter)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = NULL;
	if (limiter)
		redir->limiter = ft_strdup(limiter);
	else
		redir->limiter = NULL;
	redir->is_quoted_limiter = 0;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}
