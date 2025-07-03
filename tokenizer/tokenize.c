/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:18:36 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/19 16:07:04 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_token_addition(t_node **node, t_add_to_node *n)
{
	if (n->j > 0)
	{
		n->tmp[n->j] = '\0';
		add_node_to_list(node, n->tmp);
		n->j = 0;
	}
	return (1);
}

int	handle_space_char(t_node **node, t_add_to_node *n, char c, char in_quote)
{
	if (c == ' ' && in_quote == 0)
	{
		handle_token_addition(node, n);
		return (1);
	}
	return (0);
}

static int	process_char(t_process_context *ctx, char c)
{
	int	res;

	if ((c == '|' || c == '<' || c == '>') && ctx->in_quote == 0)
	{
		res = handle_operator_chars(ctx->node, ctx->cmd, ctx->i, ctx->n);
		if (res == 0)
			return (0);
		return (1);
	}
	if (handle_space_char(ctx->node, ctx->n, c, ctx->in_quote))
	{
		(*ctx->i)++;
		return (1);
	}
	ctx->n->tmp[ctx->n->j++] = c;
	(*ctx->i)++;
	return (1);
}

int	parse_cmd(t_node **node, char *cmd, t_add_to_node *n)
{
	int					i;
	char				in_quote;
	char				c;
	int					res;
	t_process_context	ctx;

	i = 0;
	in_quote = 0;
	ctx.node = node;
	ctx.n = n;
	ctx.in_quote = in_quote;
	ctx.cmd = cmd;
	ctx.i = &i;
	while (cmd[i])
	{
		c = cmd[i];
		update_quote(c, &ctx.in_quote);
		res = process_char(&ctx, c);
		if (res == 0)
			return (0);
	}
	return (1);
}

int	split_into_tokens(t_node **node, char *cmd)
{
	t_add_to_node	*n;

	n = init_tmp(cmd);
	if (!parse_cmd(node, cmd, n))
	{
		free(n->tmp);
		free(n);
		free_list(node);
		*node = NULL;
		return (0);
	}
	handle_token_addition(node, n);
	free(n->tmp);
	free(n);
	return (1);
}
