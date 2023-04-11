/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:10:44 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/10 15:35:33 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static char	*join_strings(char **str_array)
{
	int		index;
	char	*result;
	char	*tmp;

	index = 0;
	result = NULL;
	while (str_array[index])
	{
		if (!result)
			result = ft_strdup(str_array[index]);
		else
		{
			tmp = ft_strjoin(result, str_array[index]);
            free(result);
            result = tmp;
		}
		if (!result)
			return (NULL); // fix later
		index++;
	}
	return (result);
}

static int	regular_interpreter(char **str_array, int index, t_mini *mini)
{
	char	*regular;
	char	*result;

	regular = interpret_quotes(str_array[index]);
	if (!regular)
		return (FAILURE);
	result = dollar_interpreter(regular, mini);
	free(regular);
	if (!result)
		return (FAILURE);
	free(str_array[index]);
	str_array[index] = result;
	return (SUCCESS);
}

static int	literal_interpreter(char **str_array, int index)
{
	char	*literal;

	literal = interpret_quotes(str_array[index]);
	if (!literal)
		return (FAILURE);
	free(str_array[index]);
	str_array[index] = literal;
	return (SUCCESS);
}

char	*interpreter(char *str, t_mini *mini)
{
	int		index;
	int		ret;
	char	**cut;
	char	*result;

	if (!str)
		return (NULL);
	cut = cut_into_pieces(str);
	if (!cut)
		return (NULL);
	index = 0;
	while (cut[index])
	{
		if (cut[index][0] == SINGLE_QUOTE)
			ret = literal_interpreter(cut, index);
		else
			ret = regular_interpreter(cut, index, mini);
		if (ret == FAILURE)
			return (free_double_array(cut), NULL);
		index++;
	}
	result = join_strings(cut);
	free_double_array(cut);
	if (!result)
		return (NULL);
	return (result);
}
