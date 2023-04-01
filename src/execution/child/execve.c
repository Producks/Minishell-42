/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/31 23:31:16 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
