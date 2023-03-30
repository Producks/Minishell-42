/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/30 10:00:31 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../main/init.h"

void	ft_exit(t_mini *mini)
{
	printf("Buh Bye\n");
	//free_struct(mini);
	exit (0);
}
