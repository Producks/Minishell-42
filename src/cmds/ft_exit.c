/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/01 06:12:39 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../init.h"

void	ft_exit(t_mini *mini)
{
	free_struct(mini);
	printf("Buh Bye\n");
	exit (0);
}