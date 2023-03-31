/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:02:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/30 00:49:17 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

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
	if (literal.ret == -1)
		return (free(literal.str), NULL);
	literal.array = ft_split(literal.str, 29);
	if (!literal.array)
		return (free(literal.str), print_errno(ENOMEM), NULL);
	literal_check_errors(&literal); // check more case later
	if (literal.ret == -1)
		return (free(literal.str), ft_free(literal.array), NULL);
	return (free(literal.str), literal.array);
}
