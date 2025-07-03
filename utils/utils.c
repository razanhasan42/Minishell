/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:32:30 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/23 19:24:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		free(envp[i++]);
	free(envp);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*tmp;

	while (cmd_list)
	{
		free_list(&cmd_list->tokens);
		free(cmd_list->tokens);
		tmp = cmd_list->next;
		free_argv(cmd_list->argv);
		if (cmd_list->redir_list)
			free_redirections(&cmd_list->redir_list);
		free(cmd_list);
		cmd_list = tmp;
	}
}

void	assign_token_types(t_node *tokens)
{
	while (tokens)
	{
		if (tokens->value && ft_strcmp(tokens->value, "|") == 0)
			tokens->type = TOKEN_PIPE;
		else if (ft_strcmp(tokens->value, "<") == 0)
			tokens->type = REDIR_INPUT;
		else if (ft_strcmp(tokens->value, ">") == 0)
			tokens->type = REDIR_OUTPUT;
		else if (ft_strcmp(tokens->value, ">>") == 0)
			tokens->type = REDIR_APPEND;
		else if (ft_strcmp(tokens->value, "<<") == 0)
			tokens->type = REDIR_HEREDOC;
		else
			tokens->type = WORD;
		tokens = tokens->next;
	}
}
