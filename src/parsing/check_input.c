/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:47:59 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/28 14:30:08 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../struct.h"
#include "../../lib/libft.h"
#include "../pipex.h"
#include "../cmds/cmds.h"

int	check_if_utils(t_mini *mini)
{
	if (ft_strncmp(mini->cmd[0], "echo", 4) == 0)
		echo(mini->cmd); // to do
	else if (ft_strncmp(mini->cmd[0], "cd", 2) == 0)
		cd("test"); // to do
	else if (ft_strncmp(mini->cmd[0], "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(mini->cmd[0], "export", 6) == 0)
		export(); // to do
	else if (ft_strncmp(mini->cmd[0], "unset", 5) == 0)
		unset(); // to do
	else if (ft_strncmp(mini->cmd[0], "env", 3) == 0)
		env(mini->env_copy); // to do
	else if (ft_strncmp(mini->cmd[0], "exit", 4) == 0)
		ft_exit(); // to do
	return (1);
}

int check_input(t_mini *mini)
{
	mini->cmd = ft_split(mini->message, ' ');
	if (check_if_utils(mini) == 0)
		ft_free(mini->cmd);
	else
		create_child(mini->message, mini->env_copy);
	return (1);
}
