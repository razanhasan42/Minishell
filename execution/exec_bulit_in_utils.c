/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulit_in_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:22:51 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/17 12:46:43 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_numeric_argument(const char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_exit_argument_errors(char **argv, t_env *env_list,
		t_command *cmd_list)
{
	if (!is_valid_numeric_argument(argv[1]))
	{
		printf("exit: %s: numeric argument required\n", argv[1]);
		free_env_list(env_list);
		free_command_list(cmd_list);
		exit(2);
	}
	if (argv[2])
	{
		printf("bash : exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	builtin_exit(char **argv, t_env *env_list, t_command *cmd_list,
		int last_status)
{
	int	status;
	int	error;

	status = 0;
	printf("exit\n");
	if (argv[1])
	{
		error = handle_exit_argument_errors(argv, env_list, cmd_list);
		if (error)
			return (error);
		status = ft_atoi(argv[1]);
	}
	else
		status = last_status;
	free_env_list(env_list);
	free_command_list(cmd_list);
	exit(status);
}

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}

int	exec_builtin_cmd(t_command *cmd, t_env **env, int exit_status)
{
	int	ret;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		ret = builtin_echo(cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ret = builtin_cd(cmd->argv, env);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ret = builtin_pwd();
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ret = builtin_export(cmd->argv, env);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ret = builtin_unset(cmd->argv, env);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ret = builtin_env(*env);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ret = builtin_exit(cmd->argv, *env, cmd, exit_status);
	else if (ft_strcmp(cmd->argv[0], "expr") == 0)
		ret = builtin_expr(cmd->argv);
	else
		ret = 1;
	return (ret);
}
