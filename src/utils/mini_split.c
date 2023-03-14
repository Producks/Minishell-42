/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:26:11 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/14 17:06:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
 #include <string.h>

extern int g_exit_status;

// static char	**ft_free_mem(char **ptr)
// {
// 	int	i;

// 	i = 0;
// 	while (ptr[i])
// 	{
// 		free(ptr[i]);
// 		i++;
// 	}
// 	free(ptr);
// 	return (NULL);
// }

// static void	ft_special(const char *str, unsigned int start, t_split *a)
// {
// 	int		i;
// 	char	c;
// 	char	*temp;

// 	i = 0;
// 	c = str[start];
// 	if (str[start] == c)
// 	{
// 		i = start + 1;
// 		while (str[i] != c && str[i] != '\0')
// 			i++;
// 		if (str[i] == '\0')
// 			return ;
// 		i -= start - 1;
// 	}
// 	temp = ft_substr(str, start, i);
// 	a->i += ft_strlen(temp) - 1;
// 	a->ptr[a->nmbcount] = ft_strtrim(temp, "'\"");
// 	free(temp);
// 	a->check_sep = 69;
// 	if (a->ptr[a->nmbcount] == NULL)
// 		return ;
// 	a->nmbcount += 1;
// }

// static int	ft_length(char const *s, char c, int i)
// {
// 	int	length;

// 	length = 0;
// 	while (s[i] != c && s[i])
// 	{
// 		length++;
// 		i++;
// 	}
// 	return (length);
// }

// static char	**get_size(char const *s, char c, t_split *a)
// {
// 	a->word_count = 1;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 			a->word_count++;
// 		if (*s == 39 || *s == '\"')
// 		{
// 			a->c = *s++;
// 			while (*s != a->c && *s != '\0')
// 				s++;
// 			if (*s == '\0')
// 				return (NULL);
// 			if (*s == a->c || *s == '\0')
// 				s++;
// 		}
// 		while (*s && *s != c)
// 			s++;
// 	}
// 	a->str = (char **)malloc(sizeof(char *) * a->word_count);
// 	if (!a->str)
// 		return (NULL);
// 	a->str[a->word_count - 1] = NULL;
// 	return (a->str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	t_split	a;

// 	if (!s)
// 		return (NULL);
// 	a.ptr = get_size(s, c, &a);
// 	a.i = -1;
// 	a.nmbcount = 0;
// 	a.check_sep = 0;
// 	while (a.ptr && s[++a.i])
// 	{
// 		if (s[a.i] == c)
// 			a.check_sep = 0;
// 		if (s[a.i] == 39 || s[a.i] == '\"')
// 			ft_special(s, a.i, &a);
// 		if (s[a.i] != c && a.check_sep++ == 0)
// 		{
// 			a.ptr[a.nmbcount] = ft_substr(s, a.i, ft_length(s, c, a.i));
// 			if (a.ptr[a.nmbcount++] == NULL)
// 				return (ft_free_mem(a.ptr));
// 		}
// 	}
// 	return (a.ptr);
// }

int	get_number_elements(const char *str, char sep)
{
	int		count;
	int		type;

	count = 0;
	while (*str)
	{
		type = 0;
		while (*str == sep)
			str++;
		if (*str)
			count++;
		if (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTE)
		{
			if (*str == SINGLE_QUOTE)
				type = SINGLE_QUOTE;
			else
				type = DOUBLE_QUOTE;
			str++;
			while (*str != type && *str)
				str++;
		}
		while (*str && *str != sep)
			str++;
	}
	return (count);
}

char	**mini_split(const char *str, char sep)
{
	t_split split;

	if (!str)
		return (NULL);
	split.nbr_elements = get_number_elements(str, sep);
	printf("%d\n", split.nbr_elements);
	if (split.nbr_elements == -1)
		return (NULL);
	split.array = malloc(sizeof(char *) * split.nbr_elements);
	if (!split.array)
		return (NULL);
	return (NULL);
}


void	test_function(t_mini *mini)
{
	mini_split("echo \"'\"hello\"'\"        ", ' ');
	exit (0);
}
		// while (*str == sep)
		// 	str++;
		// if (*str)
		// 	count++;
		// if (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTE)
		// {
		// 	if (*str == SINGLE_QUOTE)
		// 		type = SINGLE_QUOTE;
		// 	else
		// 		type = DOUBLE_QUOTE;
		// 	str++;
		// 	while (*str != type && !str)
		// 		str++;
		// 	if (!str)
		// 	{
		// 		g_exit_status = 0xFF; // change later
		// 		break ;
		// 	}
		// }
		// str++;