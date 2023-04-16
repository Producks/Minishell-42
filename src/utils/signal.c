/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:33:52 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 17:42:14 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../parsing/parsing.h"

extern int	g_exit_status;

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
		g_exit_status = 1;
	}
}

void	heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_exit_status = 6969;
		close(STDIN_FILENO);
	}
}

void	signals_handler_child(bool is_heredoc)
{
	if (is_heredoc == true)
	{
		signal(SIGINT, heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	signals_handler_parent(bool mute, bool is_interactive)
{
	if (mute == true)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (is_interactive == true)
	{
		signal(SIGINT, interactive_shell);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, regular_shell);
		signal(SIGQUIT, regular_shell);
	}
}
