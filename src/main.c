/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/22 05:54:20 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include "check_input.h"

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

void	handle(int num)
{
	printf("\nEXIT!\n");
	exit (0);
}

int	main(void)
{
	char *message;

	signal(SIGINT, handle);
	printf(GRN "Minishell >" RESET);
	message = readline(" ");
	while (check_input(message) != 0)
	{
		free (message);
		printf(GRN "Minishell >" RESET);
		message = readline(" ");
	}
	printf("Bye bye!\n");
	free (message);
	return (0);
}