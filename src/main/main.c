/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/05 04:42:19 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <errno.h>
#include "../parsing/check_input.h"
#include "struct.h"
#include "init.h"
#include "../../lib/libft.h"

//Global variable for exit status
//int	g_exit_status = 0;

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
	printf("EXIT\n");
	exit (0);
}

int add_(int num)
{
    int result;
    __asm__ __volatile__(
        "mov %1, %0\n\t"
        "xor %%eax, %%eax\n\t" // clear the eax register
        "jmp loop_check\n\t"
        "loop_body:\n\t"
        "inc %0\n\t"
        "loop_check:\n\t"
        "inc %%eax\n\t"
        "cmp $11, %%eax\n\t"
        "jne loop_body\n\t" // jump to loop body if not equal
        : "=r" (result)
        : "r" (num)
        : "%eax"
    );
    return result;
}


int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	signal(SIGINT, handle);
	if (init_struct(&mini, envp) == -1)
		return (ENOMEM);
	printf(GRN "Minishell >" RESET);
	if (!mini.message)
		mini.message = readline(" ");
	while (check_input(&mini) != 0)
	{
		free (mini.message);
		printf(GRN "Minishell >" RESET);
		mini.message = readline(" ");
	}
	free_struct(&mini);
	return (0);
}
