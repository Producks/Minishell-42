/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:33:52 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 17:16:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termcap.h> // remove later ?
#include <termios.h>
#include <unistd.h>
#include "../parsing/parsing.h"

extern int	g_exit_status;

// void	silence_signal()
// {
// 	char *term = getenv("TERM");
//     if (tgetent(NULL, term) != 1)
//         printf("Error: could not load termcap database.\n");
//     struct termios termios_p;
//     tcgetattr(STDIN_FILENO, &termios_p);
//     termios_p.c_lflag &= ~(ICANON | ECHO | ISIG);
//     tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
// }

void	regular_shell(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (signal == SIGQUIT)
		write(STDERR_FILENO, "Quit: 3\n", 8);
}

void	interactive_shell(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_handler(bool parent, bool mute, bool is_interactive)
{
	if (parent == true)
	{
		if (mute == true)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
		}
		else if (is_interactive)
		{
			signal(SIGINT, interactive_shell);
			signal(SIGQUIT, SIG_IGN);
		}
		else
		{
			signal(SIGINT, regular_shell);
			signal(SIGQUIT, regular_shell);
		}
		return ;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
