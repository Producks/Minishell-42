/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/01 23:43:03 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../execution.h"
#include "../../main/signal.h"

void	wait_for_child_process(t_cmds *cmds)
{
	int	ret_status;

	ret_status = g_exit_status;
	while (cmds)
	{
		waitpid(cmds->pid, &ret_status, 0);
		g_exit_status = WEXITSTATUS(ret_status);
		cmds = cmds->next;
	}
}

static void	create_fork(t_mini *mini)
{
	bool	is_built_in;
	int		ret;

	is_built_in = check_if_builtin(mini);
	if (is_built_in && mini->is_one_cmd)
	{
		built_ins(mini);
		return ;
	}
	mini->cmds_list->pid = fork();
	if (mini->cmds_list->pid == FAILURE)
		perror("Minishell");
	if (mini->cmds_list->pid == SUCCESS)
	{
		child_signal();
		if (is_built_in == true)
		{
			ret = built_ins(mini);
			child_cleanup_no_cmds(mini);
			exit(ret);
		}	
		run_cmd(mini);
	}
}

/*Will handle errors later prototype to see if the idea works*/
int	create_child_process(t_mini *mini)
{
	int			ret;

	mini->head_cmd = mini->cmds_list;
	ret = 0;
	while (mini->cmds_list)
	{
		ret = handle_io_redirections(mini); // close pipe check later
		if (ret == SUCCESS)
			create_fork(mini);
		mini->cmds_list = mini->cmds_list->next;
		restore_parent_file_descriptors(mini);
	}
	mini->cmds_list = mini->head_cmd;
	return (ret);
}
