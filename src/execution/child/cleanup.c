/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:26:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 14:14:36 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../utils/utils.h"
#include "../../input/input.h"

void	check_if_pipe_cleanup(t_mini *mini)
{
	if (mini->cmds_list->redir_list != NULL)
	{
		if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE) // double check later
		{
			if (mini->cmds_list->redir_list->out == true)
				close(mini->cmds_list->next->fd_in);
		}
	}
}

void	free_double_array_execve(char **str, char **nope)
{
	
	int	index;

	index = 0;
	if (!str || !nope)
		return ;
	if (str == nope)
		return ;
	while (str[index])
		free(str[index++]);
	free (str);
}

void	free_linked_list_execve(t_mini *mini)
{
	t_cmds	*previous;

	previous = NULL;
	while (mini->head_cmd)
	{
		if (mini->head_cmd->redir_list)
			clean_redir_list(mini->head_cmd);
		free_double_array_execve(mini->head_cmd->cmds, mini->current_cmds);
		previous = mini->head_cmd;
		mini->head_cmd = mini->head_cmd->next;
		free(previous);
		previous = NULL;
	}
}

void	child_cleanup_no_cmds(t_mini *mini)
{
	close(STDOUT_FILENO);
	close(mini->fd_in);
	close(mini->fd_out);
	close(STDIN_FILENO);
	check_if_pipe_cleanup(mini);
	free_linked_list_mini(&mini->head_cmd);
	free_struct(mini);
	exit (0);
}

void	child_cleanup_execve_failure(t_mini *mini)
{
	perror("Minishell");
	exit(1);
}

void	child_cleanup_before_command(t_mini *mini)
{
	close(mini->fd_in);
	close(mini->fd_out);
	check_if_pipe_cleanup(mini);
	mini->current_cmds = mini->cmds_list->cmds;
	free_linked_list_execve(mini);
	if (mini->message)
		free (mini->message);
}

void	child_cleanup_command_not_found(t_mini *mini)
{
	print_string_error("Minishell: command not found: ");
	print_string_error(mini->cmds_list->cmds[0]);
	write(STDERR_FILENO, "\n", 1);
	close(mini->fd_in);
	close(mini->fd_out);
	check_if_pipe_cleanup(mini);
	free_linked_list_mini(&mini->head_cmd);
	free_struct(mini);
	exit (127);
}
