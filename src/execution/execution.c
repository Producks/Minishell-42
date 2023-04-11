/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:59:40 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 15:47:20 by cperron          ###   ########.fr       */
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
	
	if (mini->delete_file == true)
		unlink("MiniHeredoc");
	mini->skip_waiting = false;
	mini->is_one_cmd = false;
	mini->delete_file = false;
}

void	execution(t_mini *mini)
{
	check_if_one_command(mini);
	create_child_process(mini);
	wait_for_child_process(mini->cmds_list, mini->skip_waiting);
	parent_cleanup(mini);
	//perror("Minishell");
}