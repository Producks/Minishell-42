/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:02:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 15:28:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	literal_check_errors(t_literal *literal)
{
	literal->index = 0;
	while (literal->array[literal->index])
	{
		check_bracket_error(literal, literal->array[literal->index]);
		if (literal->ret == FAILURE)
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
			if (literal->ret == FAILURE)
				return ;
		}
		literal->index++;
	}
}

static void	init_literal_struct(t_literal *literal)
{
	literal->index = 0;
	literal->i = 0;
	literal->count = 0;
	literal->ret = 0;
	literal->flag = 0;
	literal->type = 0;
	literal->array = NULL;
}

char	**literal_tokenization(t_mini *mini)
{
	t_literal	literal;

	init_literal_struct(&literal);
	count_literal_string(&literal, mini->message);
	if (!literal.count)
		return (NULL);
	literal.str = malloc(sizeof(char) * literal.count);
	if (!literal.str)
		return (print_errno(ENOMEM), NULL);
	literal_string_sep(&literal, mini->message);
	if (literal.ret == FAILURE)
		return (free(literal.str), NULL);
	literal.array = ft_split(literal.str, 29);
	if (!literal.array)
		return (free(literal.str), print_errno(ENOMEM), NULL);
	literal_check_errors(&literal);
	if (literal.ret == FAILURE)
		return (free(literal.str), free_double_array(literal.array), NULL);
	return (free(literal.str), literal.array);
}
