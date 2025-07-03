/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saabo-sh <saabo-sh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:06:12 by saabo-sh          #+#    #+#             */
/*   Updated: 2025/06/14 16:46:41 by saabo-sh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_escape(char c)
{
	if (c == 'n')
		ft_putchar('\n');
	else if (c == 't')
		ft_putchar('\t');
	else if (c == 'a')
		ft_putchar('\a');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'r')
		ft_putchar('\r');
	else if (c == 'v')
		ft_putchar('\v');
	else if (c == '\\')
		ft_putchar('\\');
	else
	{
		ft_putchar('\\');
		if (c)
			ft_putchar(c);
	}
}

void	print_with_escape(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			handle_escape(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
}

int	is_valid_ne_flag(const char *arg, int *print_newline, int *enable_escape)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (arg[i] == 'n')
			*print_newline = 0;
		else if (arg[i] == 'e')
			*enable_escape = 1;
		else
			return (0);
		i++;
	}
	return (1);
}

int	parse_echo_flags(char **argv, int *print_newline, int *enable_escape)
{
	int	i;

	i = 1;
	*print_newline = 1;
	*enable_escape = 0;
	while (argv[i] && is_valid_ne_flag(argv[i], print_newline, enable_escape))
		i++;
	return (i);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	print_newline;
	int	enable_escape;

	i = parse_echo_flags(argv, &print_newline, &enable_escape);
	while (argv[i])
	{
		if (enable_escape)
			print_with_escape(argv[i]);
		else
			printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (print_newline)
		printf("\n");
	return (0);
}
