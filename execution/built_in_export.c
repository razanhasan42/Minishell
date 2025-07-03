/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:37:15 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/16 19:30:02 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_assignment(char *arg, t_env **env)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (!equal || equal == arg)
	{
		return (1);
	}
	key = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		ft_putstr_fd("export: memory allocation error\n", 2);
		return (1);
	}
	set_env_value_exec(env, key, value);
	free(key);
	free(value);
	return (0);
}

int	export_list(t_env *env)
{
	t_env	*sorted_list;
	t_env	*current;

	sorted_list = NULL;
	current = env;
	while (current)
	{
		add_env_variable(&sorted_list, current->name, current->value);
		current = current->next;
	}
	sort_env_list(&sorted_list);
	current = sorted_list;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
	free_env_list(sorted_list);
	return (0);
}

int	builtin_export(char **argv, t_env **env)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!argv[1])
		return (export_list(*env));
	while (argv[i])
	{
		if (export_assignment(argv[i], env) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}

int	builtin_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
