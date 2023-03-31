/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:24:25 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/28 21:27:30 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	restore_stdin_fileno(t_mini *mini)
{
	if (dup2(mini->fd_in, STDIN_FILENO) == FAILURE)
		return (print_errno(1), FAILURE);
	return (SUCCESS);
}

static int	restore_stdout_fileno(t_mini *mini)
{
	mini->cmds_list->fd_out = dup(STDOUT_FILENO);
	if (mini->cmds_list->fd_out == FAILURE)
		return (print_errno(1), FAILURE);
	if (dup2(mini->fd_out, STDOUT_FILENO) == FAILURE)
		return (print_errno(1), FAILURE);
	mini->cmds_list->fd_out_bool = true;
	return (SUCCESS);
}

int	restore_previous_stdout_fileno(t_mini *mini)
{
	if (mini->cmds_list->fd_out_bool == true)
	{
		mini->cmds_list->fd_out_bool = false;
		if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
			return (print_errno(1), FAILURE);
		if (close(mini->cmds_list->fd_out) == FAILURE)
			return (print_errno(1), FAILURE);
	}
	return (SUCCESS);
}

int	check_fd_heredoc(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (mini->cmds_list->fd_in != mini->cmds_list->fd_in && mini->cmds_list->fd_in != 0)
		ret = restore_stdin_fileno(mini);
	if (ret == FAILURE)
		return (FAILURE);
	if (mini->cmds_list->fd_out != mini->cmds_list->fd_in && mini->cmds_list->fd_out != 0)
		ret = restore_stdout_fileno(mini);
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
