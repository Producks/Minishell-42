/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:41:03 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/10 18:21:57 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		if (current->in_type != 0)
			close (current->fd_in);
		if (current->out_type != 0)
			close (current->fd_out);
		current = current->next;
	}
	return (0);
}

int	pipe_heredoc(t_mini *mini)
{
	return (0);
}

int	pipe_append_out(t_mini *mini)
{
	return (0);
}

static int	pipe_deez_in(t_mini *mini)
{
	if (dup2(mini->cmds_link_test->fd_in, STDIN_FILENO) == -1)
		return (-1);
	if (close(mini->cmds_link_test->fd_in) == -1)
		return (-1);
	return (0);
}

static int	pipe_deez_out(t_mini *mini)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	mini->cmds_link_test->fd_out = fd[1];
	mini->cmds_link_test->next->fd_in = fd[0];
	if (dup2(mini->cmds_link_test->fd_out, STDOUT_FILENO) == -1)
		return (-1);
	if (close(mini->cmds_link_test->fd_out) == -1)
		return (-1);
	return (0);
}

static int	pipe_read_output(t_mini *mini)
{
	mini->cmds_link_test->fd_out = open(mini->cmds_link_test->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (mini->cmds_link_test->fd_out == -1)
		return (-1);
	if (dup2(mini->cmds_link_test->fd_out, STDOUT_FILENO) == -1)
		return (-1);
	if (close(mini->cmds_link_test->fd_out) == -1)
		return (-1);
	return (0);
}

static int	pipe_read_input(t_mini *mini)
{
	mini->cmds_link_test->fd_in = open(mini->cmds_link_test->infile, O_RDONLY);
	if (mini->cmds_link_test->fd_in == -1)
		return (-1);
	if (dup2(mini->cmds_link_test->fd_in, STDIN_FILENO) == -1)
		return (-1);
	if (close(mini->cmds_link_test->fd_in) == -1)
		return (-1);
	return (0);
}

int	pipe_redirection(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (mini->cmds_link_test->in_type)
	{
		if (mini->cmds_link_test->in_type == REDIRECTION_PIPE)
			ret = pipe_deez_in(mini);
		else if (mini->cmds_link_test->in_type == READ_INPUT)
			ret = pipe_read_input(mini);
		else
			ret = pipe_heredoc(mini);
	}
	if (mini->cmds_link_test->out_type && ret != -1)
	{
		if (mini->cmds_link_test->out_type == REDIRECTION_PIPE)
			ret = pipe_deez_out(mini);
		else if (mini->cmds_link_test->out_type == READ_OUTPUT)
			ret = pipe_read_output(mini);
		else
			ret = pipe_append_out(mini);
	}
	return (ret);
}
