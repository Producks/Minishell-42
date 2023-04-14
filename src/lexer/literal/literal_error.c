/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:58:04 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 15:33:51 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	literal_error_handling(t_literal *literal, const char *str, int err_nbr)
{
	write(2, str, ft_strlen(str));
	g_exit_status = err_nbr;
	literal->ret = FAILURE;
}

void	check_single_redir_error(t_literal *literal)
{
	if (isredir(literal->array[literal->index][1]))
		return (literal_error_handling(literal,
				"Minishell: Redirection to the right\n", COMMAND_LINE_ERROR));
	if (!literal->array[literal->index + 1])
		return (literal_error_handling(literal,
				"Minishell: Empty arg to the right\n", COMMAND_LINE_ERROR));
	if (isredir(literal->array[literal->index + 1][0]))
		return (literal_error_handling(literal,
				"Minishell: Is redir right bad\n", COMMAND_LINE_ERROR));
}

void	check_double_redir_error(t_literal *literal)
{
	if (literal->type == '|')
		return (literal_error_handling(literal,
				"double pipe bozo\n", COMMAND_LINE_ERROR));
	if (!literal->array[literal->index + 1])
		return (literal_error_handling(literal,
				"No argument to the right\n", COMMAND_LINE_ERROR));
	if (isredir(literal->array[literal->index + 1][0]))
		return (literal_error_handling(literal,
				"Is redir right bad\n", COMMAND_LINE_ERROR));
}

void	check_pipe_error(t_literal *literal)
{
	if (!literal->array[literal->index + 1])
		return (literal_error_handling(literal,
				"Minishell: Argument missing to the right of the pipe\n",
				COMMAND_LINE_ERROR));
	if (literal->array[literal->index + 1][0] == '|')
		return (literal_error_handling(literal,
				"Minishell: Double pipe syntax error\n", COMMAND_LINE_ERROR));
	if (literal->index == 0)
		return (literal_error_handling(literal,
				"Minishell: Argument missing to the left of the pipe\n",
				COMMAND_LINE_ERROR));
}

void	check_bracket_error(t_literal *literal, const char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == DOLLAR_SIGN)
		{
			index++;
			if (!str[index])
				break ;
			if (str[index] == '{')
			{
				while (str[index] != '}' && str[index])
					index++;
				if (!str[index])
					return (literal_error_handling(literal,
							"Minishell: Incorect input\n", 2));
			}
		}
		index++;
	}
}
