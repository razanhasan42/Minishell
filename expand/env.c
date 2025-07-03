/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:57:39 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/05/29 17:58:38 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env_variable(t_env **env_list, char *name, char *value)
{
	t_env	*current;
	t_env	*new_env;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = *env_list;
	*env_list = new_env;
}

char	*get_env_value(t_env *env_list, char *var_name)
{
	t_env	*temp;

	if (!var_name)
		return (NULL);
	temp = env_list;
	while (temp)
	{
		if (!temp->name)
			return (NULL);
		if (ft_strcmp(temp->name, var_name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*equal_pos;
	char	*name;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (equal_pos)
		{
			name = ft_strndup(envp[i], equal_pos - envp[i]);
			value = ft_strdup(equal_pos + 1);
			add_env_variable(&env_list, name, value);
			free(name);
			free(value);
		}
		i++;
	}
	return (env_list);
}

void	swap_env_vars(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	b->name = temp_name;
	a->value = b->value;
	b->value = temp_value;
}

void	sort_env_list(t_env **env_list)
{
	t_env	*i;
	t_env	*j;

	if (!(*env_list))
		return ;
	i = *env_list;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (strcmp(i->name, j->name) > 0)
				swap_env_vars(i, j);
			j = j->next;
		}
		i = i->next;
	}
}
