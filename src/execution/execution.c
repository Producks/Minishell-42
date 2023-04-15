/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:59:40 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/15 12:20:09 by ddemers          ###   ########.fr       */
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

static void	parent_cleanup(t_mini *mini)
{
	mini->cmds_list = free_linked_list_mini(&mini->cmds_list);
	mini->skip_waiting = false;
	mini->is_one_cmd = false;
}

void	execution(t_mini *mini)
{
	check_if_one_command(mini);
	if (check_if_heredoc(mini) == FAILURE)
	{
		parent_cleanup(mini);
		return ;
	}
	create_child_process(mini);
	wait_for_child_process(mini->cmds_list, mini->skip_waiting);
	parent_cleanup(mini);
}
