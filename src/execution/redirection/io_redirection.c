/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 08:40:34 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/10 16:06:21 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	redirect_input_to_pipe(t_mini *mini)
{
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	redirect_output_to_pipe(t_mini *mini)
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

int	redirect_output_append_to_file(t_mini *mini)
{
	mini->cmds_list->fd_out = open(mini->cmds_list->redir_list->filename,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (mini->cmds_list->fd_out == FAILURE)
		return (FAILURE);
	if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	redirect_output_to_file(t_mini *mini)
{
	mini->cmds_list->fd_out = open(mini->cmds_list->redir_list->filename,
			O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (mini->cmds_list->fd_out == FAILURE)
		return (FAILURE);
	if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	redirect_input_from_file(t_mini *mini)
{
	mini->cmds_list->fd_in = open(mini->cmds_list->redir_list->filename,
			O_RDONLY);
	if (mini->cmds_list->fd_in == FAILURE)
		return (print_errno(1), FAILURE);
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	redirect_input_from_heredoc(t_mini *mini)
{
	if (!mini->cmds_list->redir_list->tmp_file)
		return (FAILURE);
	mini->cmds_list->fd_in = open(mini->cmds_list->redir_list->tmp_file, O_RDONLY);
	if (mini->cmds_list->fd_in == FAILURE)
		return (print_errno(1), FAILURE);
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
