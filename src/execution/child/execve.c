/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/27 14:27:09 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../main/init.h"

void	child_cleanup(t_mini *mini)
{
	fprintf(stderr, "Child: %s %p\n", mini->env_copy[0], mini->env_copy[0]);
	mini->env_copy[0][0] = 'Z';
	fprintf(stderr, "Child: %s %p\n", mini->env_copy[0], mini->env_copy[0]);
	free (mini->message);
	close(mini->fd_in);
	close(mini->fd_out);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE) // check later !!dangerous!!
	{
		close(mini->fd_out);
		close(mini->cmds_list->next->fd_in);
	}
	exit (0);
}

void	run_cmd(t_mini *mini)
{
	char	*path;
	int		index;

	//child_cleanup(mini);
	if (!mini->cmds_list->cmds)
		child_cleanup(mini);
	path = find_path(mini); // check later for errors leaks etc..
	execve(path, mini->cmds_list->cmds, mini->env_copy);
	exit(0);
}