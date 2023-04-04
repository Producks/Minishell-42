/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:54:51 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/04 15:59:57 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

static int	count_number_elements(char *str)
{
	size_t	count;
	int		index;
	char	type;

	count = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == SINGLE_QUOTE || str[index] == DOUBLE_QUOTE)
		{
			type = str[index++];
			count++;
			while (str[index] != type)
				index++;
			index++;
		}
		else
		{
			count++;
			while (str[index] && str[index] != SINGLE_QUOTE && str[index] != DOUBLE_QUOTE)
				index++;
		}
	}
	return (count);
}

static int	get_len(const char *str, char c)
{
	int		index;
	char	type;

	index = 0;
	if (c != SINGLE_QUOTE && c != DOUBLE_QUOTE)
	{
		while (str[index] && str[index] != SINGLE_QUOTE && str[index] != DOUBLE_QUOTE)
			index++;
		return (index);
	}
	type = str[index++];
	while (str[index] != type)
		index++;
	index++;
	return (index);
}

static char	*cut_deez(char *str)
{
	int		index;
	size_t	len;
	char	type;
	char	*ret;

	index = 0;
	len = 0;
	type = str[index];
	len = get_len(str, type);
	ret = ft_substr(str, 0, len);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*get_cut_string(char *str, int index)
{
	int		count;
	char	type;
	char	*cut;

	count = 0;
	while (count != index)
	{
		if (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTE)
		{
			type = *str++;
			count++;
			while (*str != type)
				*str++;
			*str++;
			continue ;
		}
		count++;
		while (*str != SINGLE_QUOTE && *str != DOUBLE_QUOTE)
			*str++;
	}
	cut = cut_deez(str);
	if (!cut)
		return (NULL);
	return (cut);
}

/*This is my last resort*/
char	**cut_into_pieces(char *str)
{
	char	**cut;
	size_t	index;
	size_t	nbr_of_element;

	nbr_of_element = count_number_elements(str);
	cut = ft_calloc(1, sizeof(char *) * (nbr_of_element + 1));
	if (!cut)
		return (NULL);
	index = 0;
	while (index < nbr_of_element)
	{
		cut[index] = get_cut_string(str, index);
		if (!cut[index])
			return (ft_free(cut), NULL);
		index++;
	}
	return (cut);
}
