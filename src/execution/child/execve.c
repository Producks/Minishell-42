/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/24 19:39:26 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	run_cmd(t_mini *mini)
{
	char	*path;
	int		index;
	char	*test;

	index = 0;
	// if (check_if_built_ins(mini))
	// 	exit (0);
	//check_if_executable(mini);
	path = find_path(mini);
	mini->cmds_list->cmds[0] = path; //leaks
	execve(path, mini->cmds_list->cmds, mini->env_copy);
	exit(0);
}