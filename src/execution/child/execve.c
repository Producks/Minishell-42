/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/27 23:09:04 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../main/init.h"

void	child_cleanup(t_mini *mini)
{
	fprintf(stderr, "Cherhrehreherhild: %s %p\n", mini->env_copy[0], mini->env_copy[0]);
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
	// fprintf(stderr, "Child: %p n", mini->cmds_list->cmds);
	if (!mini->cmds_list->cmds)
		child_cleanup(mini);
	path = find_path(mini); // check later for errors leaks etc..
	execve(path, mini->cmds_list->cmds, mini->env_copy);
	perror("Minishell");
	exit(0);
}