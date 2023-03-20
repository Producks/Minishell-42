/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:12:49 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 23:17:02 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/*
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define DOLLAR_SIGN  
*/
int	tokens_interpreter(t_mini *mini, char **literal)
{
	int	index;
	int	j;
	int	ret;

	ret = 0;
	index = 0;
	while (literal[index])
	{
		j = 0;
		while (literal[index][j])
		{
			if (literal[index][j] == DOLLAR_SIGN)
			{
				if (dollar_interpreter(mini, literal, index))
					return (FAILURE);
			}
			else if (literal[index][j] == SINGLE_QUOTE || literal[index][j] == DOUBLE_QUOTE)
			{
				if (interpret_quotes(mini, literal[index]))
					return (FAILURE);
			}
			j++;
		}
		index++;
	}
	for (int i = 0; literal[i]; i++)
		printf("%s\n", literal[i]);
	exit (0);
	return (SUCCESS);
}
