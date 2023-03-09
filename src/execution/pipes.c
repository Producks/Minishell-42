/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:41:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/09 17:37:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_restore(t_mini *mini)
{
	dup2(mini->fd_in, STDIN_FILENO);
	dup2(mini->fd_out, STDOUT_FILENO);
}

int	close_pipes_subroutine(t_mini *mini)
{
	t_cmds *current;

	current = mini->cmds_link_test;
	while (current)
	{
		if (current->fd_in != mini->fd_in)
		{
			printf("Close:In:%d\n", current->fd_in);
			close (current->fd_in);
		}
		if (current->out_type != 0)
		{
			printf("Close:Out:%d\n", current->fd_out);
			close (current->fd_out);
		}
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

	if (!mini->cmds_link_test->out_type && !mini->cmds_link_test->in_type)
	{
		pipe_restore(mini);
		return (0);
	}
	if (mini->cmds_link_test->in_type)
	{
		if (mini->cmds_link_test->in_type == RED_INPUT)
			mini->cmds_link_test->fd_in = open(mini->cmds_link_test->infile, O_RDONLY);
		if (!mini->cmds_link_test->fd_in)
			puts("ERROR");
		printf("Make in:%d\n", mini->cmds_link_test->fd_in);
		dup2(mini->cmds_link_test->fd_in, STDIN_FILENO);
	}
	if (mini->cmds_link_test->out_type)
	{
		if (mini->cmds_link_test->out_type == 50)
		{
			ret = pipe(fd);
			if (ret == -1)
				puts("error");
			mini->cmds_link_test->fd_out = fd[1];
			mini->cmds_link_test->next->fd_in = fd[0];
			printf("Make:out%d in%d\n", mini->cmds_link_test->fd_out, mini->cmds_link_test->next->fd_in);
			dup2(mini->cmds_link_test->fd_out, STDOUT_FILENO);
		}
	}
	return (0);
}