/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:09:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 11:11:34 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static int	double_quote_interpreter(t_mini *mini, char *str)
{
	return (SUCCESS);
}

static int	single_quote_interpreter(t_mini *mini, char *str)
{
	return (SUCCESS);
}

int	interpret_quotes(t_mini *mini, char *str)
{
	int	index;
	int	ret;

	index = 0;
	ret = 0;
	if (str[index] == SINGLE_QUOTE)
		ret = single_quote_interpreter(mini, str);
	else
		ret = double_quote_interpreter(mini, str);
	if (ret == -1)
		return (FAILURE);
	return (SUCCESS);
}