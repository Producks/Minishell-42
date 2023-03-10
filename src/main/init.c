/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:32:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/10 11:33:26 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libs/Libft/libft.h"
#include "init.h"

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
	mini->cmd = ft_free(mini->cmd);
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
	mini->cmd = NULL;
	mini->cmds_link_test = NULL;
	mini->fd_in = dup(0);
	mini->fd_out = dup(1);
	return (0);
}
