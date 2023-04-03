/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/01 19:28:24 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "signal.h"
#include "struct.h"
#include "init.h"
#include "../parsing/parsing.h"

//Global variable for exit status
int	g_exit_status = 0;

static void	print_welcome_message(void)
{
	char	*user;

	user = getenv("USER");
	printf("Welcome %s to this garbage project\n", user);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	init_signals();
	if (init_struct(&mini, envp) == -1)
		return (ENOMEM);
	print_welcome_message();
	read_input(&mini);
	free_struct(&mini);
	return (0);
}
