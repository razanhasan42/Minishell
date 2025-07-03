/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:04:34 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/19 09:10:10 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_exec_context(t_exec_context *ctx, t_node *tokens, t_env *env,
		t_command *old_cmd)
{
	ctx->tokens = &tokens;
	ctx->cmd = old_cmd;
	ctx->env = env;
	ctx->cmd_path = NULL;
	ctx->envp = NULL;
	ctx->argv = convert_tokens_to_argv(tokens);
	if (!ctx->argv || !ctx->argv[0])
		cleanup_and_exit(ctx, 0);
}

static void	handle_builtin_command(t_exec_context *ctx, t_command *cmd_list,
		int exit_status)
{
	if (is_exit_command(cmd_list))
	{
		free_argv(ctx->argv);
		free_envp(ctx->envp);
	}
	exec_builtin_cmd(cmd_list, &ctx->env, exit_status);
	cleanup_and_exit(ctx, exit_status);
}

static void	handle_external_command(t_exec_context *ctx)
{
	if (!ctx->argv[0] || ft_strlen(ctx->argv[0]) == 0)
	{
		ft_putstr_fd(": command not found\n", 2);
		cleanup_and_exit(ctx, 127);
	}
	ctx->cmd_path = find_in_path(ctx->argv[0], ctx->env);
	ctx->envp = env_to_envp(ctx->env);
	if (!ctx->cmd_path)
	{
		ft_putstr_fd(ctx->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_and_exit(ctx, 127);
	}
	if (execve(ctx->cmd_path, ctx->argv, ctx->envp) == -1)
	{
		perror("execve failed");
		cleanup_and_exit(ctx, 126);
	}
	cleanup_and_exit(ctx, 0);
}

static void	handle_and_execute_command(t_exec_context *ctx, t_command *cmd_list,
		int exit_status)
{
	if (is_builtin(cmd_list))
		handle_builtin_command(ctx, cmd_list, exit_status);
	else
	{
		handle_external_command(ctx);
	}
}

void	exec_command(t_node *tokens, t_env *env, t_command *old_cmd,
		t_command *cmd_list)
{
	t_exec_context	ctx;

	init_exec_context(&ctx, tokens, env, old_cmd);
	handle_and_execute_command(&ctx, cmd_list, 0);
}
