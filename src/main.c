/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 15:31:43 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "./utils/utils.h" 
#include "./utils/struct.h"

//remove later
#include "./parsing/parsing.h"

// //Global variable for exit status
int		g_exit_status = 0;
char	**g_env_test = NULL;

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	init_parent_signals();
	if (init_struct(&mini, envp) == FAILURE)
		return (ENOMEM);
	#ifndef TESTER
	#  define TESTER 0
	#endif
	g_env_test = mini.env_copy;
	if (TESTER == true)
	{
		mini.message = ft_strdup(argv[1]);
		lexer(&mini);
		free_struct(&mini);
		return (0);
	}
	print_startup();
	read_input(&mini);
	free_struct(&mini);
	return (0);
}