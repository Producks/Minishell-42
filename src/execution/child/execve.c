/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 00:14:16 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../parsing/parsing.h"

void	run_cmd(t_mini *mini)
{
	char	*path;
	int		index;

	if (!mini->current_cmds[0])
		child_cleanup_no_cmds(mini);
	path = find_path(mini); // check later for errors leaks etc..
	if (!path)
		child_cleanup_command_not_found(mini);
	execve(path, mini->current_cmds, mini->env_copy);
	free(path);
	child_cleanup_execve_failure(mini);
}
