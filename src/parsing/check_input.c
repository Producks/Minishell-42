/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:47:59 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/04 09:12:20 by ddemers          ###   ########.fr       */
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
		echo(mini->cmd); 
	else if (ft_strcmp(mini->cmd[0], "cd") == 0)
		cd(mini);
	else if (ft_strcmp(mini->cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(mini->cmd[0], "export") == 0)
		ft_export(mini);
	else if (ft_strcmp(mini->cmd[0], "unset") == 0)
		unset(mini);
	else if (ft_strcmp(mini->cmd[0], "env") == 0)
		env(mini->env_copy);
	else if (ft_strcmp(mini->cmd[0], "exit") == 0)
		ft_exit(mini);
	return (1);
}

int check_input(t_mini *mini)
{
	mini->cmd = ft_split(mini->message, ' ');
	if (check_if_utils(mini) == 0)
		ft_free(mini->cmd);
	mini->cmd = ft_free(mini->cmd);
	return (1);
}
