/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expandable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:36:48 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 14:36:58 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	check_expandable(char c)
{
	if ((ft_isalpha(c) || ft_isdigit(c) || c == UNDERSCORE))
		return (true);
	return (false);
}