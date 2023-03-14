/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:33:52 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/13 14:51:36 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// wrong signal command place holder for now
//try and make this work with ctrl+D intead of ctr+c so it doesn't seg fault TODO
void	handle(int num)
{
	printf("EXIT\n");
	rl_replace_line("Minishell > ", 0);
	// exit (0);
}

void	init_signals(void)
{
	signal(SIGINT, handle);
}