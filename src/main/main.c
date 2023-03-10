/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/10 12:00:44 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "signal.h"
#include "struct.h"
#include "init.h"
#include "../parsing/parsing.h"

//Global variable for exit status
//int	g_exit_status = 0;

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	init_signals();
	if (init_struct(&mini, envp) == -1)
		return (ENOMEM);
	read_input(&mini);
	free_struct(&mini);
	return (0);
}
