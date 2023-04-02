/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:09:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/01 18:09:51 by ddemers          ###   ########.fr       */
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

char	*interpret_quotes(char *str)
{
	size_t	count;
	char	*result;
	char	*copy;

	copy = ft_strdup(str);
	if (!copy)
		return (print_errno(ENOMEM), NULL);
	count = count_quotes(copy);
	if (count == 0)
		return (copy);
	result = malloc(sizeof(char) * (ft_strlen(copy) - count) + 1);
	if (!result)
		return (print_errno(ENOMEM), free(copy), NULL);
	quote_interpreter(copy, result);
	free (copy);
	return (result);
}
