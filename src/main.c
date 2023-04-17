/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 20:08:37 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/utils.h" 
#include "./utils/struct.h"

//remove later
#include "./parsing/parsing.h"

//Global variable for exit status
int		g_exit_status = 0;

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	signals_handler_parent(false, false);
	if (init_struct_mini(&mini, envp) == FAILURE)
		return (errno);
	#ifndef TESTER
	#  define TESTER 0
	#endif
	if (TESTER == true)
	{
		mini.message = ft_strdup(argv[1]);
		lexer(&mini);
		free_struct_mini(&mini);
		return (0);
	}
	print_startup();
	g_exit_status = read_input(&mini);
	rl_clear_history();
	free_struct_mini(&mini);
	printf("exit\n");
	return (g_exit_status);
}
