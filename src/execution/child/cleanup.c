/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:26:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 02:19:59 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../utils/utils.h"
#include "../../input/input.h"

void	check_if_pipe_cleanup(t_mini *mini)
{
	if (mini->cmds_list->redir_list != NULL)
	{
		if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
		{
			if (mini->cmds_list->redir_list->out == true)
				close(mini->cmds_list->next->fd_in);
		}
	}
}

void	child_cleanup_no_cmds(t_mini *mini)
{
	free_struct_mini(mini);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	exit (0);
}

void	child_cleanup_execve_failure(t_mini *mini)
{
	perror("Minishell");
	free_struct_mini(mini);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	exit(1);
}

void	cleanup(t_mini *mini)
{
	rl_clear_history();
	close(mini->fd_in);
	close(mini->fd_out);
	check_if_pipe_cleanup(mini);
	mini->current_cmds = mini->cmds_list->cmds;
	free_linked_list_execve(mini);
	mini->cmds_list = NULL;
	if (mini->message)
	{
		free (mini->message);
		mini->message = NULL;
	}
}

void	child_cleanup_command_not_found(t_mini *mini)
{
	print_string_error("Minishell: command not found: ");
	print_string_error(mini->current_cmds[0]);
	write(STDERR_FILENO, "\n", 1);
	free_struct_mini(mini);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	exit (127); // check
}
