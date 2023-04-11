/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:22:43 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/10 15:52:02 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

void	create_file_name(char *dst, int number)
{
	ft_strncpy(dst, ".Miniheredoc", 12);
	if (number <= 9)
	{
		dst[12] = '0';
		dst[13] = number + 48;
		dst[14] = '\0';
	}
	else
	{
		dst[12] = (number / 10) + 48;
		dst[13] = (number % 10) + 48;
		dst[14] = '\0';
	}
	return ;
}
