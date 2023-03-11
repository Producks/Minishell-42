/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:01:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/10 22:30:09 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "../../libs/Libft/libft.h"

int	echo(char **message)
{
	int		index;
	bool	check_n;

	index = 1;
	check_n = false;
	while (message[index])
	{
		if ((ft_strcmp(message[index], "-n") == 0) && (index == 1))
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
	return (0);
}
