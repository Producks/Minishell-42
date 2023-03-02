/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:47:59 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 12:26:03 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../main/struct.h"
#include "../../lib/libft.h"
#include "../execution/pipex.h"
#include "../cmds/cmds.h"

int	check_if_utils(t_mini *mini)
{
	if (ft_strcmp(mini->cmd[0], "echo") == 0)
		echo(mini->cmd); // Check later if it still works, should be done
	else if (ft_strcmp(mini->cmd[0], "cd") == 0)
		cd("test"); // to do
	else if (ft_strcmp(mini->cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(mini->cmd[0], "export") == 0)
		ft_export(mini); // to do
	else if (ft_strcmp(mini->cmd[0], "unset") == 0)
		unset(mini); // to do
	else if (ft_strcmp(mini->cmd[0], "env") == 0)
		env(mini->env_copy); // should be done
	else if (ft_strcmp(mini->cmd[0], "exit") == 0)
		ft_exit(mini); // to do
	return (1);
}

int check_input(t_mini *mini)
{
	mini->cmd = ft_split(mini->message, ' ');
	if (check_if_utils(mini) == 0)
		ft_free(mini->cmd);
	// else
	// 	create_child(mini->message, mini->env_copy);
	//env(mini->env_list);
	env(mini->env_copy);
	ft_free(mini->cmd);
	return (0);
}
