/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:01:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/28 13:02:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "../../lib/libft.h"

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
			printf("%s", message[index]);
		if (message[index + 1] && message[index])
			printf(" ");
		index++;
	}
	if (check_n == false)
		printf("\n");
	return (0);
}
