/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 19:47:59 by ddemers          ###   ########.fr       */
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
	path = find_path(mini);
	if (!path)
		child_cleanup_command_not_found(mini);
	execve(path, mini->current_cmds, mini->env_copy);
	free(path);
	child_cleanup_execve_failure(mini);
}
