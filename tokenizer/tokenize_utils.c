/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:26:50 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/19 16:10:03 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_add_to_node	*init_tmp(const char *cmd)
{
	t_add_to_node	*ctx;

	ctx = malloc(sizeof(t_add_to_node));
	if (!ctx)
		exit(1);
	ctx->j = 0;
	ctx->tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!ctx->tmp)
		exit(1);
	return (ctx);
}

static int	parse_operator(char *cmd, int *i, char *op)
{
	memset(op, 0, 3);
	op[0] = cmd[*i];
	if (cmd[*i] == '<' && cmd[*i + 1] == '<' && cmd[*i + 2] == '<')
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (0);
	}
	if ((cmd[*i + 1] == '>' || cmd[*i + 1] == '<') && cmd[*i + 1] == cmd[*i])
		op[1] = cmd[++(*i)];
	if (cmd[*i] == '|' && cmd[*i + 1] == '|')
	{
		printf("bash: syntax error near unexpected token `%s`\n", op);
		return (0);
	}
	(*i)++;
	return (1);
}

static int	handle_operators(char *cmd, int *i, t_node **node)
{
	char	op[3];

	if (!parse_operator(cmd, i, op))
		return (0);
	while (cmd[*i] == ' ')
		(*i)++;
	if (op[0] == '|' && ft_strncmp(&cmd[*i], "exit", 4) == 0 && cmd[*i
			+ 4] == '\0')
		return (0);
	if (!cmd[*i])
	{
		printf("bash: syntax error near unexpected token `%s`\n", op);
		return (0);
	}
	add_node_to_list(node, op);
	return (1);
}

void	update_quote(char c, char *in_quote)
{
	if (c == '\'' || c == '"')
	{
		if (*in_quote == 0)
			*in_quote = c;
		else if (*in_quote == c)
			*in_quote = 0;
	}
}

int	handle_operator_chars(t_node **node, char *cmd, int *i, t_add_to_node *n)
{
	int	j;

	handle_token_addition(node, n);
	j = *i;
	while (j > 0 && cmd[j - 1] == ' ')
		j--;
	if (j == 0 && cmd[*i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (!handle_operators(cmd, i, node))
		return (0);
	return (1);
}
