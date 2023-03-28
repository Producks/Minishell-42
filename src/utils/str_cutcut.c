/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cutcut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:22:23 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/23 22:20:49 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

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

// CHECK LATER IF CORRECT AND NO CONDITIONAL JUMP
static size_t	len_result(char *original, char *replacement, char *to_replace)
{
	size_t	len;

	len = ft_strlen(original) - ft_strlen(to_replace);
	len = len + ft_strlen(replacement) + 1;
	return (len);
}

char	*strncmp_cut(const char *haystack, const char *needle, size_t len,
			size_t	i)
{
	if (len == 0)
		return (NULL);
	while (*haystack && i <= len)
	{
		if (*haystack == SINGLE_QUOTE)
		{
			haystack++;
			len--;
			while (*haystack != SINGLE_QUOTE)
			{
				haystack++;
				len--;
			}
		}
		if (*haystack == *needle && ft_strncmp(haystack, needle, i) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
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
	position = strncmp_cut(original, to_replace,
			ft_strlen(original), ft_strlen(to_replace));
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
	return (result);
}
