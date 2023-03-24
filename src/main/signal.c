/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:33:52 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/23 12:08:51 by ddemers          ###   ########.fr       */
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
// wrong signal command place holder for now
//try and make this work with ctrl+D intead of ctr+c so it doesn't seg fault TODO
void	q_handle(int num)
{
	silence_signal();
	// exit (0);
}

void	place_holder(int num)
{
	g_exit_status = 69;
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, place_holder);
	signal(SIGQUIT, q_handle);
}