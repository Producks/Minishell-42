/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:33:52 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 09:32:54 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>
#include "../parsing/parsing.h"

extern int	g_exit_status;

void	silence_signal()
{
	char *term = getenv("TERM");
	
    if (tgetent(NULL, term) != 1)
        printf("Error: could not load termcap database.\n");

    struct termios termios_p;
	
    tcgetattr(STDIN_FILENO, &termios_p);
    termios_p.c_lflag &= ~(ICANON | ECHO | ISIG);
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

void	parent_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		rl_redisplay();
		return ;
	}
}

void	child_signal_handler(int signal)
{
	if (signal == SIGINT)
		g_exit_status = 130;
	else if (signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
    	g_exit_status = 131;
	}
}

void	init_child_signal(void)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
}

void	init_parent_signals(void)
{
	signal(SIGINT, parent_signal_handler);
	signal(SIGQUIT, parent_signal_handler);
}
