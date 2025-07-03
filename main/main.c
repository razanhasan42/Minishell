/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:50 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/23 14:52:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	read_value(char **command, t_tokenize_params *params,
		t_shell_context *context)
{
	int	read_val;

	read_val = read_and_validate_command(command, context);
	if (!read_val)
	{
		params->command = NULL;
		return (0);
	}
	if (read_val == -1)
	{
		if (*command)
			free(*command);
		*command = ft_strdup("");
		return (1);
	}
	if (g_signal_status == 130)
	{
		context->last_exit_status = g_signal_status;
		g_signal_status = 0;
	}
	return (1);
}

static void	init_params(t_tokenize_params *params, t_shell_context *context,
		t_env **env_list)
{
	static t_node		*linked_list;
	static t_command	*cmd_list;
	static int			heredoc_cancelled;
	static char			*command;

	linked_list = NULL;
	cmd_list = NULL;
	heredoc_cancelled = 0;
	command = NULL;
	if (!read_value(&command, params, context))
		return ;
	params->command = command;
	params->linked_list = &linked_list;
	params->cmd_list = &cmd_list;
	params->heredoc_cancelled = &heredoc_cancelled;
	params->context = context;
	params->env_list = env_list;
}

static bool	process_command(t_shell_context *context, t_env **env_list,
		t_tokenize_params *params)
{
	init_params(params, context, env_list);
	if (!params->command)
		return (false);
	if (!*(params->command))
	{
		free(params->command);
		return (true);
	}
	if (!tokenize_and_build_commands(params))
	{
		if (!(*params->heredoc_cancelled))
			context->last_exit_status = 2;
		if (params->command)
		{
			free(params->command);
			params->command = NULL;
		}
		return (true);
	}
	return (true);
}

static int	handle_shell_loop(t_shell_context *context, t_env **env_list)
{
	t_tokenize_params		params;
	t_exec_cleanup_params	exec_params;

	if (!process_command(context, env_list, &params))
		return (0);
	if (!params.cmd_list || !*(params.cmd_list))
		return (1);
	exec_params.command = params.command;
	exec_params.linked_list = *(params.linked_list);
	exec_params.cmd_list = *(params.cmd_list);
	exec_params.env_list = params.env_list;
	execute_and_cleanup(&exec_params, context, params.heredoc_cancelled);
	return (1);
}

int	main(int ac, char **argv, char **envp)
{
	t_shell_context	context;
	t_env			*env_list;
	int				status;

	if (ac <= 0)
		return (1);
	context.program_name = argv[0];
	context.last_exit_status = 0;
	env_list = create_env_list(envp);
	while (1)
	{
		init_signal();
		if (!handle_shell_loop(&context, &env_list))
			break ;
	}
	status = context.last_exit_status;
	free_env_list(env_list);
	return (status);
}
