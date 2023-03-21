/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:09:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/20 21:16:35 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static size_t	count_quotes(const char *str, char type)
{
	size_t	count;
	int		index;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == type)
			count++;
		index++;
	}
	return (count);
}

static char	*quote_interpreter(t_mini *mini, char *str, char type)
{
	size_t	count;
	int		index;
	int		j;
	char	*result;

	index = 0;
	j = 0;
	count = count_quotes(str, type); // maybe add later cause issue
	result = malloc(sizeof(char) * ((ft_strlen(str) - count) + 1));
	if (!result)
		return (NULL);
	while (str[index])
	{
		if (str[index] != type)
			result[j++] = str[index];
		index++;
	}
	result[j] = '\0';
	return (result);
}

int	interpret_quotes(t_mini *mini, char **tokens, int index)
{
	char	*double_result;
	char	*single_result;

	single_result = quote_interpreter(mini, tokens[index], SINGLE_QUOTE);
	if (!single_result)
		return (FAILURE);
	double_result = quote_interpreter(mini, single_result, DOUBLE_QUOTE);
	if (!double_result)
		return (free(single_result), FAILURE);
	free (single_result);
	free (tokens[index]);
	tokens[index] = double_result;
	return (SUCCESS);
}
