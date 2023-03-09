/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:41:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/08 22:09:33 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_restore(t_mini *mini, int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

int	close_pipes_subroutine(t_mini *mini)
{
	t_cmds *current;

	current = mini->cmds_link_test;
	while (current)
	{
		if (current->fd_in != STDIN_FILENO)
			close (current->fd_in);
		if (current->fd_out != STDOUT_FILENO)
			close (current->fd_out);
		current = current->next;
	}
	return (0);
}

int	pipe_redirection(t_mini *mini)
{
	int	fd[2];
	int	fdin;
	int	fdout;
	int	ret;
	
	if (mini->cmds_link_test->infile)
		fdin = open(mini->cmds_link_test->infile, O_RDONLY);
	if (mini->cmds_link_test->fd_in != STDIN_FILENO)
	{
		// dup2();
	}
	return (0);
}