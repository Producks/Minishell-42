/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:58:04 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/29 19:18:49 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	literal_error_handling(t_literal *literal, const char *str, int err_nbr)
{
	write(2, str, ft_strlen(str));
	g_exit_status = err_nbr;
	literal->ret = -1;
}

static void	check_single_redir_error(t_literal *literal)
{
	if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
		return (literal_error_handling(literal, "Redirection to the right\n", 2));
	if (!literal->array[literal->index + 1]) // check if redir has no args to the right
		return (literal_error_handling(literal, "Empty arg to the right\n", 2));
	if (isredir(literal->array[literal->index + 1][0]))
		return (literal_error_handling(literal, "Is redir right bad\n", 2));	
}

// fix << name test
static void	check_double_redir_error(t_literal *literal)
{
	if (literal->type == '|')
		return (literal_error_handling(literal, "double pipe bozo\n", 2));
	if (!literal->array[literal->index + 1]) // check if redir has no args to the right
		return (literal_error_handling(literal, "No argument to the right\n", 2));
	if (isredir(literal->array[literal->index + 1][0]))
		return (literal_error_handling(literal, "Is redir right bad\n", 2));
}

static void	check_pipe_error(t_literal *literal)
{
	if (literal->array[literal->index + 1][0] == '|')
		return (literal_error_handling(literal, "double pipe bozo\n", 2));
	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
		return (literal_error_handling(literal, "Argument missing to right of the pipe\n", 2));
	if (literal->index == 0) // check if pipe has no args to the left
		return (literal_error_handling(literal, "Argument missing to left of the pipe\n", 2));
}

static void	check_bracket_error(t_literal *literal, const char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == DOLLAR_SIGN)
		{
			index++;
			if (str[index] == '{')
			{
				while (str[index] != '}' && str[index])
					index++;
				if (!str[index])
					return (literal_error_handling(literal, "BOZO LMAO SO FUCKING BAD🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 🤡 \n", 2));
			}
		}
		index++;
	}
}

void	literal_check_errors(t_literal *literal)
{
	literal->index = 0;
	while (literal->array[literal->index])
	{
		check_bracket_error(literal, literal->array[literal->index]);
		if (literal->ret == -1)
			return ;
		literal->index++;
	}
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


// static void	check_pipe_error(t_literal *literal)
// {
// 	if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
// 		return (literal_error_handling(literal, "Redirection next to the pipe\n", 2));
// 	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
// 		return (literal_error_handling(literal, "Argument missing to right of the pipe\n", 2));
// 	if (literal->index == 0) // check if pipe has no args to the left
// 		return (literal_error_handling(literal, "Argument missing to left of the pipe\n", 2));
// 	if (isredir(literal->array[literal->index - 1][0]))
// 		return (literal_error_handling(literal, "Argument missing to left of the pipe\n", 2));
// }