/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/30 10:01:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../execution.h"
#include "../../cmds/cmds.h"

int	check_if_built_ins(t_mini *mini)
{
	// if (ft_strcmp(mini->cmds_list->cmds[0], "echo") == 0)
	// 	return (echo(mini->cmds_list->cmds));
	// else if (ft_strcmp(mini->cmd[0], "cd") == 0)
	// 	cd(mini);
	// else if (ft_strcmp(mini->cmd[0], "pwd") == 0)
	// 	pwd();
	// else if (ft_strcmp(mini->cmd[0], "export") == 0)
	// 	ft_export(mini);
	// else if (ft_strcmp(mini->cmd[0], "unset") == 0)
	// 	unset(mini);
	// else if (ft_strcmp(mini->cmd[0], "env") == 0)
	// 	env(mini->env_copy);
	if (ft_strcmp(mini->cmds_list->cmds[0], "exit") == 0)
		ft_exit(mini);
	return (1);
}

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
	check_if_built_ins(mini); // FIX LATER BOZO
	mini->cmds_list->pid = fork();
	if (mini->cmds_list->pid == FAILURE)
		perror("Minishell");
	if (mini->cmds_list->pid == SUCCESS)
		run_cmd(mini);
}

/*Will handle errors later prototype to see if the idea works*/
int	create_child_process(t_mini *mini)
{
	t_cmds		*head;
	int			ret;

	head = mini->cmds_list;
	ret = 0;
	while (mini->cmds_list)
	{
		if (handle_io_redirections(mini) == FAILURE) // close pipe check later
		{
			mini->cmds_list = mini->cmds_list->next;
			restore_parent_file_descriptors(mini);
			continue ;
		}
		create_fork(mini);
		mini->cmds_list = mini->cmds_list->next;
		restore_parent_file_descriptors(mini);
	}
	mini->cmds_list = head;
	return (ret);
}
