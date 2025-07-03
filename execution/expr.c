/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:33:48 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/12 11:10:43 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	expr_usage(void)
{
	printf("usage: expr num1 operator num2\n");
	return (1);
}

static int	expr_division_by_zero(void)
{
	printf("expr: division by zero\n");
	return (1);
}

static int	expr_unknown_operator(char *op)
{
	printf("expr: unknown operator: %s\n", op);
	return (1);
}

static int	expr_calculate(int num1, int num2, char *op, int *result)
{
	if (ft_strcmp(op, "+") == 0)
		*result = num1 + num2;
	else if (ft_strcmp(op, "-") == 0)
		*result = num1 - num2;
	else if (ft_strcmp(op, "*") == 0)
		*result = num1 * num2;
	else if (ft_strcmp(op, "/") == 0)
	{
		if (num2 == 0)
			return (expr_division_by_zero());
		*result = num1 / num2;
	}
	else
		return (expr_unknown_operator(op));
	return (0);
}

int	builtin_expr(char **argv)
{
	int	num1;
	int	num2;
	int	result;

	if (!argv[1])
		return (expr_usage());
	if (!argv[2])
	{
		printf("%s\n", argv[1]);
		return (0);
	}
	if (!argv[3] || argv[4])
		return (expr_usage());
	num1 = ft_atoi(argv[1]);
	num2 = ft_atoi(argv[3]);
	if (expr_calculate(num1, num2, argv[2], &result) != 0)
		return (1);
	printf("%d\n", result);
	return (0);
}
