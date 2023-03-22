/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expandable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:54:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/22 14:10:43 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static bool	check_expandable(char c)
{
	if ((ft_isalpha(c) || ft_isdigit(c) || c == UNDERSCORE))
		return (true);
	return (false);
}

static size_t	get_length(const char *str)
{
	size_t	length;
	int		index;

	index = 0;
	length = 0;
	while (str[index] && str[index] != DOLLAR_SIGN)
		index++;
	index++;
	if (str[index] == '{')
		index++;
	if (!check_expandable(str[index])) // refacto here later
		return (0);
	if (ft_isdigit(str[index]))
		return (0);
	index++;
	length++;
	while (check_expandable(str[index++]))
		length++;
	return (length);
}

static char *get_str(const char *str, size_t length)
{
	int		index;
	int		j;
	char	*ret_str;

	index = 0;
	j = 0;
	ret_str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	while (str[index] && str[index] != DOLLAR_SIGN)
		index++;
	index++;
	while (check_expandable(str[index]))
		ret_str[j++] = str[index++];
	ret_str[j] = '\0';
	return (ret_str);
}

static char	*env_test(t_mini *mini, char **literal, int index)
{
	int	i;
}

static char	*get_env(t_mini *mini, char **literal, int index)
{
	size_t	length;
	char	*str;
	int		i;

	length = get_length(literal[index]);
	str = get_str(literal[index], length);
	if (!str)
		return (NULL);
	length = ft_strlen(str);
	i = 0;
	while (mini->env_copy[i])
	{
		if (!ft_strcmp(mini->env_copy[i], str))
		{
			if (mini->env_copy[i][length + 1] == '=')
				return (get_env_str(mini, literal, index));
			i++;
			continue ;
		}
		i++;
	}
	return (free(str), NULL);
}

int	dollar_expandable(t_mini *mini, char **literal, int index)
{
	char	*env_str;

	env_str = get_env(mini, literal, index);
	if (!env_str)
		return (FAILURE);
	printf("%s\n", env_str);
	exit (0);
	return (SUCCESS);
}
