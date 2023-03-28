/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:09:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/25 21:15:55 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static size_t	count_quotes(char *str)
{
	size_t	count;
	int		index;
	char	type;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == SINGLE_QUOTE || str[index] == DOUBLE_QUOTE)
		{
			type = str[index++];
			while (str[index] != type)
				index++;
			count += 2;
		}
		index++;
	}
	return (count);
}

static void	quote_interpreter(char *copy, char *result)
{
	int		index;
	int		j;
	char	type;

	index = 0;
	j = 0;
	while (copy[index])
	{
		if (copy[index] == SINGLE_QUOTE || copy[index] == DOUBLE_QUOTE)
		{
			type = copy[index];
			index++;
			while (copy[index] != type)
				result[j++] = copy[index++];
			index++;
			continue ;
		}
		result[j++] = copy[index++];
	}
	result[j] = '\0';
}

int	interpret_quotes(t_mini *mini, char **tokens, int index)
{
	size_t	count;
	char	*result;
	char	*copy;

	copy = ft_strdup(tokens[index]);
	if (!copy)
		return (print_errno(ENOMEM), FAILURE);
	count = count_quotes(copy);
	result = malloc(sizeof(char) * (ft_strlen(copy) - count) + 1);
	if (!result)
		return (print_errno(ENOMEM), free(copy), FAILURE);
	quote_interpreter(copy, result);
	free (copy);
	free (tokens[index]);
	tokens[index] = result;
	return (SUCCESS);
}
