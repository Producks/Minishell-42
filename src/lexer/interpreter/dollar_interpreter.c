/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:43:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 23:31:00 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	replace_env(t_mini *mini, char *str)
{
	return (SUCCESS);
}

int	replace_exit_status(t_mini *mini, char *str)
{
	char	*exit_status;
	char	*trim_str;

	exit_status = ft_itoa(g_exit_status);
	if (!exit_status)
		return (FAILURE);
	str = str_cutcut(str, exit_status, "$?");
	if (!str)
		return (FAILURE);
	return (SUCCESS);
}

int	 dollar_interpreter(t_mini *mini, char **literal, int index)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (literal[index][i])
	{
		if (literal[index][i] == SINGLE_QUOTE)
		{
			i++;
			while (literal[index][i] != SINGLE_QUOTE && literal[index][i])
				i++;
		}
		if (literal[index][i] == DOLLAR_SIGN)
		{
			// if (literal[index][i + 1] == QUESTION_MARK)
			// 	ret = replace_exit_status(mini, str);
			// else
			// 	ret = replace_env(mini, str);
			// if (ret == FAILURE)
			// 	return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

// int	 dollar_interpreter(t_mini *mini, char **literal, int index)
// {
// 	int	index;
// 	int	ret;

// 	index = 0;
// 	ret = 0;
// 	while (str[index])
// 	{
// 		if (str[index] == SINGLE_QUOTE) // should be safe if checkup for token is solid
// 		{
// 			index++;
// 			while (str[index] != SINGLE_QUOTE)
// 				index++;
// 		}
// 		if (str[index] == DOLLAR_SIGN)
// 		{
// 			if (str[index + 1] == QUESTION_MARK)
// 				ret = replace_exit_status(mini, str);
// 			else
// 				ret = replace_env(mini, str);
// 			if (ret == FAILURE)
// 				return (FAILURE);
// 		}
// 		index++;
// 	}
// 	return (SUCCESS);
// }

// int	 dollar_interpreter(t_mini *mini, char **literal)
// {
// 	int	index;
// 	int	j;

// 	index = 0;
// 	while (literal[index])
// 	{
// 		j = 0;
// 		while (literal[index][j])
// 		{
// 			if (literal[index][j] == SINGLE_QUOTE)
// 			{
// 				j++;
// 				while (literal[index][j] != SINGLE_QUOTE)
// 					j++;
// 			}
// 			if (literal[index][j] == DOLLAR_SIGN)
// 			{
				
// 			}
// 		}
// 		index++;
// 	}
// }
