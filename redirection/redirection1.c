/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:08:25 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/19 15:54:00 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection(char *value)
{
	return (ft_strcmp(value, "<") == 0 || ft_strcmp(value, ">") == 0
		|| ft_strcmp(value, ">>") == 0 || ft_strcmp(value, "<<") == 0);
}

int	is_quoted(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	return ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '"' && s[len
				- 1] == '"'));
}

t_redirection	*create_redirection(t_token_type type, char *filename)
{
	t_redirection	*redir;
	char			*stripped;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_memset(redir, 0, sizeof(t_redirection));
	redir->type = type;
	stripped = strip_quotes(filename);
	redir->filename = ft_strdup(stripped);
	free(stripped);
	redir->next = NULL;
	return (redir);
}

void	handle_filename(t_node *curr, char *filename,
		t_redirection **redir_list)
{
	t_redirection	*redir;
	t_redirection	*last;

	redir = create_redirection(curr->type, filename);
	if (*redir_list == NULL)
	{
		*redir_list = redir;
	}
	else
	{
		last = *redir_list;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

int	parse_redirection(t_node *linked_list, t_redirection **redir_list)
{
	t_node	*curr;

	curr = linked_list;
	while (curr)
	{
		if (ft_strcmp(curr->value, "<") == 0 || ft_strcmp(curr->value, ">") == 0
			|| ft_strcmp(curr->value, ">>") == 0)
		{
			assign_redir_type(curr);
			if (!curr->next)
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				return (0);
			}
			handle_filename(curr, curr->next->value, redir_list);
			curr = curr->next->next;
			continue ;
		}
		curr = curr->next;
	}
	return (1);
}
