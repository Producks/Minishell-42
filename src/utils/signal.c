/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:33:52 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 03:50:40 by cperron          ###   ########.fr       */
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
struct termios saved_termios;

void	disable_echo()
{
    struct termios termios_p;
    tcgetattr(STDIN_FILENO, &termios_p);
	saved_termios = termios_p;
    termios_p.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

void	restore_terminal()
{
    // Restore the saved terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
}

void	parent_signal_handler(int signal)
{
	
	if (signal == SIGINT)
	{
		// write(STDOUT_FILENO, "p", 1);
		write(1, "\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		// return ;
	}
	// restore_terminal();
}

void	child_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "c", 1);
		write(1, "\n", STDOUT_FILENO);
		rl_redisplay();
		// disable_echo();
		g_exit_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		g_exit_status = 131;
	}
}

void	init_child_signal(void)
{
	restore_terminal();
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
	
}

void	init_parent_signals(void)
{
	disable_echo();
	signal(SIGINT, parent_signal_handler);
	signal(SIGQUIT, parent_signal_handler);
}
