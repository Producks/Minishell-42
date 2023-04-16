/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 04:12:41 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include "../execution.h"
#include "../../utils/utils.h"
#include "../../input/input.h"

void	wait_for_child_process(t_cmds *cmds, bool skip_waiting)
{
	int		ret_status;
	char	temp_buffer[15];

	if (skip_waiting == true)
		return ;
	ret_status = g_exit_status;
	while (cmds)
	{
		if (cmds->skip == false)
		{
			waitpid(cmds->pid, &ret_status, 0);
			g_exit_status = calculate_exit_status(ret_status);
		}
		if (cmds->tmp_file == true)
		{
			create_file_name(temp_buffer, cmds->count);
			unlink(temp_buffer);
		}
		cmds = cmds->next;
	}
}

static void	handle_child(t_mini *mini, bool is_built_in)
{
	int	ret;

	ret = SUCCESS;
	signals_handler_child(false);
	cleanup(mini);
	if (is_built_in == true)
	{
		ret = built_ins(mini);
		child_cleanup_no_cmds(mini);
		if (ret == 69)
			exit (0);
		exit(ret);
	}	
	run_cmd(mini);
}

static void	create_fork(t_mini *mini)
{
	bool	is_built_in;
	int		ret;

	is_built_in = check_if_builtin(mini);
	if (is_built_in && mini->is_one_cmd)
	{
		mini->current_cmds = mini->cmds_list->cmds;
		ret = built_ins(mini);
		mini->current_cmds = NULL;
		mini->skip_waiting = true;
		g_exit_status = ret;
		return ;
	}
	mini->cmds_list->pid = fork();
	if (mini->cmds_list->pid == FAILURE)
		print_errno(errno);
	if (mini->cmds_list->pid == SUCCESS)
		handle_child(mini, is_built_in);
}

int	create_child_process(t_mini *mini)
{
	int			ret;

	mini->head_cmd = mini->cmds_list;
	ret = SUCCESS;
	while (mini->cmds_list)
	{
		ret = handle_io_redirections(mini);
		if (ret == SUCCESS)
			create_fork(mini);
		if (ret == FAILURE)
			mini->cmds_list->skip = true;
		mini->cmds_list = mini->cmds_list->next;
		restore_parent_file_descriptors(mini);
	}
	mini->cmds_list = mini->head_cmd;
	return (ret);
}
