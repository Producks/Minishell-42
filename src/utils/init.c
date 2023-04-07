/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:32:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/07 00:27:11 by ddemers          ###   ########.fr       */
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
		return (-1);
	index = -1;
	while (envp[++index])
	{
		mini->env_copy[index] = ft_strdup(envp[index]);
		if (!mini->env_copy[index])
		{
			ft_free(mini->env_copy);
			return (-1);
		}
	}
	mini->env_copy[index] = NULL;
	return (0);
}

void	free_struct(t_mini *mini)
{
	mini->env_copy = ft_free(mini->env_copy);
	if (mini->message)
		free (mini->message);
	close(mini->fd_in);
	close(mini->fd_out);
}

int	init_struct(t_mini *mini, char *envp[])
{
	if (copy_env(mini, envp) == -1)
		return (-1);
	mini->message = NULL;
	mini->cmds_list = NULL;
	mini->current_cmds = NULL;
	mini->head_cmd = NULL;
	mini->is_one_cmd = false;
	mini->skip_waiting = false;
	mini->fd_in = dup(STDIN_FILENO);
	mini->fd_out = dup(STDOUT_FILENO);
	return (0);
}
