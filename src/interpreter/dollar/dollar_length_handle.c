/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_length_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:01:41 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 00:10:22 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../interpreter.h"

static char	*str_cut_remove(char *original, int index, int j)
{
	char	*result;
	bool	flag;

	if (!original)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(original) - 1));
	if (!result)
		return (NULL);
	flag = false;
	while (original[index])
	{
		if (original[index] == '$' && flag == false)
		{
			index += 2;
			flag = true;
		}
		if (!original[index])
			break ;
		result[j] = original[index];
		j++;
		index++;
	}
	result[j] = '\0';
	return (result);
}

static char	*str_cut_remove_bracket(char *original, int index, int j)
{
	bool	flag;
	char	*result;

	flag = false;
	result = malloc(sizeof(char) * (ft_strlen(original) - 2));
	if (!result)
		return (NULL);
	while (original[index])
	{
		if (original[index] == '$' && flag == false)
		{
			index += 2;
			flag = true;
		}
		if (original[index] == '}')
			index++;
		if (!original[index])
			break ;
		result[j] = original[index];
		index++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

int	dollar_length_h(t_dollar *dollar, t_mini *mini, int start)
{
	int		dollar_index;
	char	*result;

	if (!dollar->result[start + 1])
		return (SUCCESS);
	if (dollar->result[start + 1] == '{')
		result = str_cut_remove_bracket(dollar->result, 0, 0);
	else
		result = str_cut_remove(dollar->result, 0, 0);
	if (!result)
		return (print_errno(ENOMEM), FAILURE);
	free(dollar->result);
	dollar->result = result;
	return (SUCCESS);
}
