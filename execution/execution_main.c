/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:26:57 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/17 12:46:12 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "expr") == 0)
		return (1);
	return (0);
}

void	set_env_value(t_env **env_list, char *key, char *value)
{
	t_env	*current;
	t_env	*new;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new = create_env_node(key, value);
	if (!new)
		return ;
	new->next = *env_list;
	*env_list = new;
}

int	cd_to_home(t_env **env)
{
	char	*home;
	char	cwd[4096];

	home = get_env_value(*env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_value(env, "OLDPWD", cwd);
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_value(env, "PWD", cwd);
	return (0);
}

int	cd_to_path(char *path, t_env **env)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_value(env, "OLDPWD", cwd);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_value(env, "PWD", cwd);
	return (0);
}

int	builtin_cd(char **argv, t_env **env)
{
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!argv[1])
		return (cd_to_home(env));
	else
		return (cd_to_path(argv[1], env));
}
