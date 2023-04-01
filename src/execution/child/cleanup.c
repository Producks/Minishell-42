/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:26:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/01 00:34:49 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../main/init.h"

void	child_cleanup_no_cmds(t_mini *mini)
{
	close(STDOUT_FILENO);
	close(mini->fd_in);
	close(mini->fd_out);
	close(STDIN_FILENO);
	if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
	{
		if (mini->cmds_list->redir_list->out == true)
			close(mini->cmds_list->next->fd_in);
	}
	free_linked_list_mini(&mini->cmds_list);
	free_struct(mini);
	exit (0);
}

void	child_cleanup_execve_failure(t_mini *mini)
{
	perror("Minishell");
	free_linked_list_mini(&mini->cmds_list);
	free_struct(mini);
	exit(1);
}

void	child_cleanup_before_execve(t_mini *mini)
{
	close(mini->fd_in);
	close(mini->fd_out);
}

void	child_cleanup_command_not_found(t_mini *mini)
{
	print_string_error("Minishell: command not found: ");
	print_string_error(mini->cmds_list->cmds[0]);
	write(STDERR_FILENO, "\n", 1);
	free_linked_list_mini(&mini->cmds_list);
	free_struct(mini);
	exit (127);
}
