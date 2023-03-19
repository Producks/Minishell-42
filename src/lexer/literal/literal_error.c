/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:58:04 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 01:13:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

extern int	g_exit_status;

void	literal_error_handling(t_literal *literal, const char *str, int err_nbr)
{
	write(2, str, ft_strlen(str));
	g_exit_status = err_nbr;
	literal->ret = -1;
}

static void	check_single_redir_error(t_literal *literal)
{
	if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
		return (literal_error_handling(literal, "Pipe right token\n", 2));
	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
		return (literal_error_handling(literal, "Pipe right empty\n", 2));
	if (literal->index == 0) // check if pipe has no args to the left
		return (literal_error_handling(literal, "Pipe left empty\n", 2));
	if (isredir(literal->array[literal->index - 1][0]))
		return (literal_error_handling(literal, "Argument to left of pipe\n", 2));
}

static void	check_double_redir_error(t_literal *literal)
{
	// if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
	// 	return (literal_error_handling(literal, "ERRORdd\n", 2));
	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
		return (literal_error_handling(literal, "Pipe right empty\n", 2));
	if (literal->index == 0) // check if pipe has no args to the left
		return (literal_error_handling(literal, "da\n", 2));
	if (isredir(literal->array[literal->index - 1][0]))
		return (literal_error_handling(literal, "ta\n", 2));
	return ;
}

static void	check_pipe_error(t_literal *literal)
{
	if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
		return (literal_error_handling(literal, "Pipe right token\n", 2));
	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
		return (literal_error_handling(literal, "Pipe right empty\n", 2));
	if (literal->index == 0) // check if pipe has no args to the left
		return (literal_error_handling(literal, "Pipe left empty\n", 2));
	if (isredir(literal->array[literal->index - 1][0]))
		return (literal_error_handling(literal, "Argument to left of pipe\n", 2));
}

void	literal_check_errors(t_literal *literal)
{
	literal->index = 0;
	while (literal->array[literal->index])
	{
		if (isredir(literal->array[literal->index][0]))
		{
			literal->type = literal->array[literal->index][0];
			if (literal->array[literal->index][1] == literal->type)
				check_double_redir_error(literal);
			else if (literal->type == '|')
				check_pipe_error(literal);
			else
				check_single_redir_error(literal);
			if (literal->ret == -1)
				return ;
		}
		literal->index++;
	}
}
