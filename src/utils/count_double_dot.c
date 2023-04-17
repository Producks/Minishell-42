/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_double_dot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:25:40 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 23:29:16 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	count_double_dot(const char *str)
{
	int	index;
	int	count;

	count = 0;
	index = 0;
	while (str[index])
	{
		if (!ft_strncmp((str + index), "../", 3))
		{
			count++;
			index += 3;
			continue ;
		}
		break ;
	}
	if (!str[index])
		return (0);
	return (count);
}
