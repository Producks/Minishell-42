/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/30 01:09:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../main/init.h"

void	child_cleanup_no_cmds(t_mini *mini)
{
	fprintf(stderr, "Hello\n"); // maybe close pipe? fd leak
	close(mini->fd_in);
	close(mini->fd_out);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ft_free(mini->literal_token);
	free_linked_list_mini(&mini->cmds_list);
	free_struct(mini);
	exit (0);
}

void	child_cleanup_execve_failure(t_mini *mini)
{
	perror("Minishell");
	ft_free(mini->literal_token);
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
	ft_free(mini->literal_token);
	free_linked_list_mini(&mini->cmds_list);
	free_struct(mini);
	exit (127);
}

void	run_cmd(t_mini *mini)
{
	char	*path;
	int		index;

	if (!mini->cmds_list->cmds[0])
		child_cleanup_no_cmds(mini);
	path = find_path(mini); // check later for errors leaks etc..
	if (!path)
		child_cleanup_command_not_found(mini);
	child_cleanup_before_execve(mini);
	execve(path, mini->cmds_list->cmds, mini->env_copy);
	free(path);
	child_cleanup_execve_failure(mini);
}
