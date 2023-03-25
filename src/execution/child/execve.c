/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:01:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/25 13:22:03 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	run_cmd(t_mini *mini)
{
	char	*path;
	int		index;

	path = find_path(mini);
	mini->cmds_list->cmds[0] = path; //leaks
	fprintf(stderr, "%s\n", mini->cmds_list->cmds[0]);
	execve(path, mini->cmds_list->cmds, mini->env_copy);
	exit(0);
}