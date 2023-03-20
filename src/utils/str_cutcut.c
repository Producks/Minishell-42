/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cutcut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:22:23 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 18:00:45 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	copy_left_over(char *result, char *left_over)
{
	int	index;

	index = 0;
	while (left_over[index])
	{
		result[index] = left_over[index];
		index++;
	}
	result[index] = '\0';
}

static size_t	len_result(char *original, char *replacement, char *to_replace)
{
	size_t	len;

	len = (ft_strlen(original) - ft_strlen(to_replace)) + ft_strlen(replacement
			+ 1);
	return (len + 1);
}

/*Cracked*/
char	*str_cutcut(char *original, char *replacement, char *to_replace)
{
	size_t	len;
	size_t	result_len;
	char	*result;
	char	*position;

	if (!original | !replacement | !to_replace)
		return (NULL);
	position = ft_strnstr(original, to_replace, ft_strlen(original));
	if (!position)
		return (NULL);
	len = position - original;
	result_len = len_result(original, replacement, to_replace);
	result = malloc(sizeof(char) * (result_len));
	if (!result)
		return (NULL);
	ft_strncpy(result, original, len);
	ft_strncpy(result + len, replacement, ft_strlen(replacement));
	copy_left_over(result + len + ft_strlen(replacement),
		position + ft_strlen(to_replace));
	return (free (original), free (replacement), result);
}
