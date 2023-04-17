/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:56:47 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 20:25:05 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../cmds/cmds.h"

int	built_ins(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(mini->current_cmds[0], "echo") == 0)
		ret = echo(mini->current_cmds);
	else if (ft_strcmp(mini->current_cmds[0], "cd") == 0)
		ret = cd(mini);
	else if (ft_strcmp(mini->current_cmds[0], "pwd") == 0)
		ret = pwd(mini);
	else if (ft_strcmp(mini->current_cmds[0], "export") == 0)
		ret = ft_export(mini);
	else if (ft_strcmp(mini->current_cmds[0], "unset") == 0)
		ret = unset(mini, 0, 0, false);
	else if (ft_strcmp(mini->current_cmds[0], "env") == 0)
		ret = env(mini->env_copy);
	else if (ft_strcmp(mini->current_cmds[0], "exit") == 0)
		ret = ft_exit(mini);
	return (ret);
}

bool	check_if_builtin(t_mini *mini)
{
	if (ft_strcmp(mini->cmds_list->cmds[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(mini->cmds_list->cmds[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(mini->cmds_list->cmds[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(mini->cmds_list->cmds[0], "export") == 0)
		return (true);
	else if (ft_strcmp(mini->cmds_list->cmds[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(mini->cmds_list->cmds[0], "env") == 0)
		return (true);
	else if (ft_strcmp(mini->cmds_list->cmds[0], "exit") == 0)
		return (true);
	return (false);
}
