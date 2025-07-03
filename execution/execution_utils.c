/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:42:39 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/14 21:36:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_args(t_node *tokens)
{
	int		count;
	t_node	*temp;

	count = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type != REDIR_INPUT && temp->type != REDIR_OUTPUT
			&& temp->type != REDIR_APPEND && temp->type != REDIR_HEREDOC)
			count++;
		temp = temp->next;
	}
	return (count);
}

char	**convert_tokens_to_argv(t_node *tokens)
{
	int		count;
	int		i;
	char	**argv;
	t_node	*temp;

	temp = tokens;
	count = count_args(tokens);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (temp)
	{
		if (temp->type != REDIR_INPUT && temp->type != REDIR_OUTPUT
			&& temp->type != REDIR_APPEND && temp->type != REDIR_HEREDOC)
			argv[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	argv[i] = NULL;
	return (argv);
}

static char	*check_direct_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_path_dirs(char **dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin_3(dirs[i], "/", cmd);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_in_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*result;

	if (!cmd)
		return (NULL);
	path = get_env_value(env, "PATH");
	if (!path || ft_strchr(cmd, '/'))
		return (check_direct_path(cmd));
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	result = search_path_dirs(dirs, cmd);
	free_split(dirs);
	return (result);
}
