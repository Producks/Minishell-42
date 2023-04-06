/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:01:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 07:20:12 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static bool	check_echo_option(const char *str, int count)
{
	int	index;

	if (count != 1)
		return (false);
	index = 0;
	if (!str[index])
		return (false);
	if (str[index++] != '-')
			return (false);
	if (str[index++] != 'n')
		return (false);
	while (str[index])
	{
		if (str[index] != 'n')
			return (false);
		index++;
	}
	return (true);
}

int	echo(char **message)
{
	int		index;
	bool	check_n;

	index = 1;
	check_n = false;
	while (message[index])
	{
		if (check_echo_option(message[index], index))
		{
			index++;
			check_n = true;
		}
		if (message[index])
			ft_putstr_fd(message[index], 1);
		if (message[index + 1] && message[index])
			write(1, " ", 1);
		index++;
	}
	if (check_n == false)
		write(1, "\n", 1);
	g_exit_status = SUCCESS;
	return (SUCCESS);
}
