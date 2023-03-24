/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:43:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/23 22:14:21 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	replace_exit_status(char **literal, int index)
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

static int	quote_incrementer(const char *str, int index)
{
	index++;
	while (str[index] && str[index] != SINGLE_QUOTE)
		index++;
	if (!str[index])
		return (index);
	index++;
	return (index);
}

static int	dollar_dispatcher(t_mini *mini, char **literal, int index)
{
	int		j;
	int		ret;
	bool	quote;

	j = 0;
	ret = 0;
	quote = false;
	while (literal[index][j])
	{
		if (literal[index][j] == SINGLE_QUOTE)
		{
			if (quote == true)
				quote = false;
			else
				quote = true;
		}
		if (literal[index][j] == DOLLAR_SIGN && quote == false)
		{
			if (literal[index][j + 1] == QUESTION_MARK)
				ret = replace_exit_status(literal, index);
			else
				ret = dollar_expandable(mini, literal, index);
			if (ret == FAILURE)
				return (FAILURE);
		}
		j++;
	}
	return (SUCCESS);
}

int	dollar_interpreter(t_mini *mini, char **literal)
{
	int	index;
	int ret;

	index = 0;
	while (literal[index])
	{
		ret = dollar_dispatcher(mini, literal, index);
		if (ret == -1)
			return (FAILURE);
		index++;
	}
	return (SUCCESS);
}
