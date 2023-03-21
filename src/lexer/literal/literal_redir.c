/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:01:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 01:11:50 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	isredir(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static void	double_redir_check(t_literal *literal, const char *str)
{
	literal->str[literal->i++] = 29;
	literal->str[literal->i++] = str[literal->index++];
	literal->str[literal->i++] = str[literal->index++];
	literal->str[literal->i++] = 29;
}

static void	single_redir_check(t_literal *literal, const char *str)
{
	literal->str[literal->i++] = 29;
	literal->str[literal->i++] = str[literal->index++];
	literal->str[literal->i++] = 29;
}

void	check_if_redir(t_literal *literal, const char *str)
{
	if (isredir(str[literal->index]))
	{
		literal->type = str[literal->index];
		if (isredir(str[literal->index + 1]))
			double_redir_check(literal, str);
		else
			single_redir_check(literal, str);
	}
	else
		literal->str[literal->i++] = str[literal->index++];
}
