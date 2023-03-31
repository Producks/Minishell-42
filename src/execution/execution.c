/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:59:40 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/30 17:23:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	check_if_one_command(t_mini *mini)
{
	int		count;
	t_cmds	*current;

	count = 0;
	current = mini->cmds_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	if (count == 1)
		mini->is_one_cmd = true;
}

void	execution(t_mini *mini)
{
	check_if_one_command(mini);
	create_child_process(mini);
	wait_for_child_process(mini->cmds_list);
	mini->cmds_list = free_linked_list_mini(&mini->cmds_list); // fix later
	unlink("MiniHeredoc");
	mini->is_one_cmd = false;
}