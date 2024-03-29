/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 08:40:34 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 04:01:30 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	redirect_input_to_pipe(t_mini *mini)
{
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (print_errno(errno), FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (print_errno(errno), FAILURE);
	return (SUCCESS);
}

int	redirect_output_to_pipe(t_mini *mini)
{
	int	fd[2];

	if (pipe(fd) == FAILURE)
		return (print_errno(errno), FAILURE);
	mini->cmds_list->fd_out = fd[1];
	mini->cmds_list->next->fd_in = fd[0];
	if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
		return (print_errno(errno), FAILURE);
	if (close(mini->cmds_list->fd_out) == FAILURE)
		return (print_errno(errno), FAILURE);
	return (SUCCESS);
}

int	redirect_output_append_to_file(t_mini *mini)
{
	if (!mini->cmds_list->redir_list->filename)
		return (print_ambigous("Minishell: ambiguous redirect\n", 1));
	if (!mini->cmds_list->redir_list->filename[0])
		return (print_ambigous("Minishell: ambiguous redirect\n", 1));
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
	if (!mini->cmds_list->redir_list->filename)
		return (print_ambigous("Minishell: ambiguous redirect\n", 1));
	if (!mini->cmds_list->redir_list->filename[0])
		return (print_ambigous("Minishell: ambiguous redirect\n", 1));
	mini->cmds_list->fd_out = open(mini->cmds_list->redir_list->filename,
			O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (mini->cmds_list->fd_out == FAILURE)
		return (print_errno(errno), FAILURE);
	if (dup2(mini->cmds_list->fd_out, STDOUT_FILENO) == FAILURE)
		return (print_errno(errno), FAILURE);
	if (close(mini->cmds_list->fd_out) == FAILURE)
		return (print_errno(errno), FAILURE);
	return (SUCCESS);
}

int	redirect_input_from_file(t_mini *mini)
{
	if (!mini->cmds_list->redir_list->filename)
		return (print_ambigous("Minishell: ambiguous redirect\n", 1));
	if (!mini->cmds_list->redir_list->filename[0])
		return (print_ambigous("Minishell: ambiguous redirect\n", 1));
	mini->cmds_list->fd_in = open(mini->cmds_list->redir_list->filename,
			O_RDONLY);
	if (mini->cmds_list->fd_in == FAILURE)
		return (print_errno(1), FAILURE);
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (print_errno(errno), FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (print_errno(errno), FAILURE);
	return (SUCCESS);
}
