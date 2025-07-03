/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:47:40 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/19 16:25:04 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_char_to_expanded(char *expanded, char c)
{
	int		len;
	char	*new_expanded;

	if (expanded)
		len = ft_strlen(expanded);
	else
		len = 0;
	new_expanded = malloc(len + 2);
	if (!new_expanded)
		return (NULL);
	if (expanded)
	{
		ft_strlcpy(new_expanded, expanded, len + 1);
	}
	new_expanded[len] = c;
	new_expanded[len + 1] = '\0';
	return (new_expanded);
}

static char	*handle_var_expansion(char *expanded, char *original,
		t_expand_context *ctx)
{
	char	*var_expansion;
	char	*tmp;

	var_expansion = expand_var_in_string(original, ctx->state, ctx->context,
			ctx->env_list);
	if (var_expansion)
	{
		tmp = expanded;
		expanded = ft_strjoin(expanded, var_expansion);
		free(tmp);
		free(var_expansion);
	}
	else
	{
		tmp = expanded;
		expanded = append_char_to_expanded(expanded, original[ctx->state->i++]);
		free(tmp);
	}
	return (expanded);
}

char	*build_expanded_string(char *original, t_expansion_state *state,
		t_shell_context *context, t_env *env_list)
{
	char				*expanded;
	t_expand_context	ctx;

	ctx.state = state;
	ctx.context = context;
	ctx.env_list = env_list;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (original[state->i])
	{
		check_quote(original, state->i, &state->in_double_quote,
			&state->in_single_quote);
		expanded = handle_var_expansion(expanded, original, &ctx);
		if (!expanded)
			return (NULL);
	}
	return (expanded);
}

char	*get_expanded_value(t_env *env_list, char *value,
		t_shell_context *context, t_expansion_state *state)
{
	char	*expanded;
	char	*var_value;

	expanded = build_expanded_string(value, state, context, env_list);
	if (expanded)
		return (expanded);
	var_value = get_env_value(env_list, value + 1);
	if (!var_value)
		var_value = "";
	return (ft_strdup(var_value));
}

void	expand_variable(t_node **linked_list, t_shell_context *context,
		t_env *env_list)
{
	t_node				*tmp;
	t_expansion_state	state;
	char				*expanded;

	tmp = *linked_list;
	while (tmp)
	{
		if (tmp->next && tmp->next->value && ft_strcmp(tmp->value, "<<") == 0)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (tmp->value)
		{
			state.i = 0;
			state.in_double_quote = 0;
			state.in_single_quote = 0;
			expanded = get_expanded_value(env_list, tmp->value, context,
					&state);
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}
