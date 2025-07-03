/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:00:46 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/14 13:02:58 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_env(t_env *env_list)
{
	t_env	*tmp;

	ft_putstr_fd("\n\nHANDLE\n\n", 2);
	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

char	*get_variable_value(char *str, t_expansion_state *state,
		t_env *env_list)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = ++(state->i);
	while (ft_isalnum(str[state->i]) || str[state->i] == '_')
		(state->i)++;
	var_name = ft_substr(str, start, state->i - start);
	var_value = get_env_value(env_list, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

int	check_quote(char *str, int i, int *in_double_quote, int *in_single_quote)
{
	if (str[i] == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	else if (str[i] == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	return (1);
}

static char	*expand_dollar_var(char *original, t_expansion_state *state,
		t_env *env_list, t_shell_context *context)
{
	char	*var_value;
	char	*expanded;

	if (original[state->i + 1] == '?')
		return (state->i += 2, ft_itoa(context->last_exit_status));
	if (original[state->i + 1] == '0')
		return (state->i += 2, ft_strdup(context->program_name));
	if (original[state->i + 1] == '$')
		return (state->i += 2, ft_strdup("$$"));
	if (ft_isdigit(original[state->i + 1]))
		return (state->i += 2, ft_strdup(""));
	if (!ft_isalnum(original[state->i + 1]) && original[state->i + 1] != '_')
		return (state->i++, ft_strdup("$"));
	var_value = get_variable_value(original, state, env_list);
	expanded = ft_strdup(var_value);
	free(var_value);
	return (expanded);
}

char	*expand_var_in_string(char *original, t_expansion_state *state,
		t_shell_context *context, t_env *env_list)
{
	if (original[state->i] == '$' && !(state->in_single_quote))
		return (expand_dollar_var(original, state, env_list, context));
	return (NULL);
}
