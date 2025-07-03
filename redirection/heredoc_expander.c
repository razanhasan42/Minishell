/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:58:05 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/16 16:36:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_env_var(const char *line, int *i, t_env *env_list, char *result)
{
	int		j;
	char	*tmp;
	char	*var_name;
	char	*var_value;

	j = *i + 1;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	var_name = ft_substr(line, *i + 1, j - *i - 1);
	var_value = get_env_value(env_list, var_name);
	if (var_value)
		tmp = ft_strjoin(result, var_value);
	else
		tmp = ft_strjoin(result, "");
	free(var_name);
	free(result);
	*i = j;
	return (tmp);
}

char	*expand_line_with_vars(char *line, t_env *env_list)
{
	int		i;
	char	*result;
	char	*tmp;
	char	str[2];

	i = 0;
	result = ft_calloc(1, 1);
	while (line[i])
	{
		if (line[i] == '$' && ft_isalpha(line[i + 1]))
			result = append_env_var(line, &i, env_list, result);
		else
		{
			str[0] = line[i];
			str[1] = '\0';
			tmp = ft_strjoin(result, str);
			free(result);
			result = tmp;
			i++;
		}
	}
	return (result);
}

void	append_redir(t_redirection *list, t_redirection *new_redir)
{
	t_redirection	*curr;

	if (!list || !new_redir)
		return ;
	curr = list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_redir;
	new_redir->next = NULL;
}
