/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:32:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 00:52:24 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libs/Libft/libft.h"
#include "utils.h"

/*Make a copy of the envp and store it in the struct*/
static int	copy_env(t_mini *mini, char *envp[])
{
	int		count;
	int		index;

	count = 0;
	while (envp[count++])
		continue ;
	mini->env_copy = malloc(sizeof(char *) * count);
	if (!mini->env_copy)
		return (print_errno(ENOMEM), FAILURE);
	index = -1;
	while (envp[++index])
	{
		mini->env_copy[index] = ft_strdup(envp[index]);
		if (!mini->env_copy[index])
		{
			free_double_array(mini->env_copy);
			return (print_errno(ENOMEM), FAILURE);
		}
	}
	mini->env_copy[index] = NULL;
	return (SUCCESS);
}

void	free_struct(t_mini *mini)
{
	mini->env_copy = free_double_array(mini->env_copy);
	mini->current_cmds = free_double_array(mini->current_cmds);
	if (mini->message)
		free (mini->message);
	close(mini->fd_in);
	close(mini->fd_out);
}

int	init_struct(t_mini *mini, char *envp[])
{
	if (copy_env(mini, envp) == FAILURE)
		return (FAILURE);
	mini->message = NULL;
	mini->cmds_list = NULL;
	mini->current_cmds = NULL;
	mini->head_cmd = NULL;
	mini->is_one_cmd = false;
	mini->skip_waiting = false;
	mini->fd_in = dup(STDIN_FILENO);
	mini->fd_out = dup(STDOUT_FILENO);
	return (SUCCESS);
}
