/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:56:08 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/18 11:39:44 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env_value(t_env *env, const char *name, const char *value)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				perror("ft_strdup");
			return ;
		}
		env = env->next;
	}
}

static void	create_env_entry(t_env **env_ptr, const char *name,
		const char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc");
		return ;
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	if (!new_node->name || !new_node->value)
	{
		perror("ft_strdup");
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return ;
	}
	new_node->next = *env_ptr;
	*env_ptr = new_node;
}

void	set_env_value_exec(t_env **env_ptr, const char *name, const char *value)
{
	if (!env_ptr || !name || !value)
		return ;
	update_env_value(*env_ptr, name, value);
	if (!get_env_value(*env_ptr, (char *)name))
		create_env_entry(env_ptr, name, value);
}

void	cleanup_and_exit(t_exec_context *ctx, int exit_code)
{
	int	i;

	if (!ctx)
		exit(exit_code);
	if (ctx->cmd_path)
		free(ctx->cmd_path);
	if (ctx->envp)
		free_envp(ctx->envp);
	if (ctx->argv)
	{
		i = 0;
		while (ctx->argv[i])
		{
			free(ctx->argv[i]);
			i++;
		}
		free(ctx->argv);
	}
	if (ctx->cmd)
		free_command_list(ctx->cmd);
	if (ctx->env)
		free_env_list(ctx->env);
	exit(exit_code);
}
