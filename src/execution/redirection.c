/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:16:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/14 13:05:54 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	redirect_in_to_pipe(t_mini *mini)
{
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	return (SUCCESS);	
}

int	redirect_out_to_pipe(t_mini *mini)
{
	int	fd[2];

	if (pipe(fd) == FAILURE)
		return (FAILURE);
	mini->cmds_list->fd_out = fd[1];
	mini->cmds_list->next->fd_in = fd[0];
	if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	redirect_output_append(t_mini *mini)
{
	mini->cmds_list->fd_out = open(mini->cmds_list->redir_list->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (mini->cmds_list->fd_out == FAILURE)
		return (FAILURE);
	if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	redirect_output(t_mini *mini)
{
	mini->cmds_list->fd_out = open(mini->cmds_list->redir_list->filename, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (mini->cmds_list->fd_out == FAILURE)
		return (FAILURE);
	if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	redirect_input(t_mini *mini)
{
	mini->cmds_list->fd_in = open(mini->cmds_list->redir_list->filename, O_RDONLY);
	if (mini->cmds_list->fd_in == FAILURE)
		return (FAILURE);
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	restore_parent_fds(t_mini *mini)
{
	dup2(mini->fd_in, STDIN_FILENO);
	dup2(mini->fd_out, STDOUT_FILENO);
}

int	handle_redirections(t_mini *mini)
{
	int	ret;

	ret = 0;
	while (mini->cmds_list->redir_list != NULL)
	{
		if (mini->cmds_list->redir_list->in == true)
		{
			if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
				ret = redirect_in_to_pipe(mini);
			else if (mini->cmds_list->redir_list->type == READ_INPUT)
				ret = redirect_input(mini);
			else
				ret = pipe_heredoc(mini);
		}
		if (mini->cmds_list->redir_list->out == true && ret != -1)
		{
			if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
				ret = redirect_out_to_pipe(mini);
			else if (mini->cmds_list->redir_list->type == READ_OUTPUT)
				ret = redirect_output(mini);
			else
				ret = redirect_output_append(mini);
		}
		mini->cmds_list->redir_list = mini->cmds_list->redir_list->next;
	}
	return (ret);
}
