/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 17:34:43 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "cmds.h"

static int	check_if_numeric_argument(const char *str)
{
	int		index;
	long	number;

	index = 0;
	number = ft_atoi(str);
	if (number > 255)
		return (2);
	if (number < 0)
		return (1);
	while (str[index])
	{
		if (ft_isdigit(str[index]))
			return (1);
		index++;
	}
	return (0);
}

/* Nice */
int	ft_exit(t_mini *mini)
{
	size_t	count;
	int		ret;

	mini->exit = true;
	count = count_double_array(mini->current_cmds);
	if (count > 2)
	{
		write(1, "Minishell: exit: too many arguments\n", 36);
		mini->exit = false;
		return (BUILTIN_COMMAND_ERROR);
	}
	if (count == 2)
	{
		ret = check_if_numeric_argument(mini->current_cmds[1]);
		if (!ret)
			return (ft_atoi(mini->current_cmds[1]));
		write (STDERR_FILENO, "Minishell: exit: numeric argument required\n", 43);
		return (255);
	}
	return (BUILTIN_SUCCESS);
}
