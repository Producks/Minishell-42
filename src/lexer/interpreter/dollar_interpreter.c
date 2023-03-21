/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:43:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/21 13:00:16 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// static char	*get_env(t_mini *mini, char *str)
// {
// 	int		index;
// 	int		j;
// 	size_t	len;
// 	char	*str;

// 	index = 0;
// 	len = 0;
// 	j = 0;
// 	while (str[index] != DOLLAR_SIGN)
// 		index++;
// 	len = ft_strlen(str + index);
// 	str = malloc(sizeof(char) * len + 1);
// 	if (!str)
// 		return (NULL);
// 	str[j++] = str[index++];
// 	return (str);
// }

int	replace_env(t_mini *mini, char **literal, int index)
{
	// char	*env_str;

	// env_str = get_env(mini, literal[index]);
	// if (!env_str)
	// 	return (FAILURE);
	// exit (0);
	return (SUCCESS);
}

int	replace_exit_status(t_mini *mini, char **literal, int index)
{
	char	*exit_status;
	char	*trim_str;

	exit_status = ft_itoa(g_exit_status);
	if (!exit_status)
		return (FAILURE);
	trim_str = str_cutcut(literal[index], exit_status, "$?");
	if (!trim_str)
		return (free(exit_status), FAILURE);
	free (literal[index]);
	free (exit_status);
	literal[index] = trim_str;
	return (SUCCESS);
}

int	dollar_interpreter(t_mini *mini, char **literal)
{
	int	index;
	int	j;
	int ret;

	index = 0;
	ret = 0;
	while (literal[index])
	{
		j = 0;
		while (literal[index][j])
		{
			if (literal[index][j] == SINGLE_QUOTE)
			{
				j++;
				while (literal[index][j] == SINGLE_QUOTE)
					j++;
				if (!literal[index][j]) // conditional jump/invalied read careful fix later
					break ;
			}
			if (literal[index][j] == DOLLAR_SIGN)
			{
				if (literal[index][j + 1] == QUESTION_MARK)
					ret = replace_exit_status(mini, literal, index);
				else
					ret = replace_env(mini, literal, index);
				if (ret == FAILURE)
					return (FAILURE);
			}
			j++;
		}
		index++;
	}
	return (SUCCESS);
}
