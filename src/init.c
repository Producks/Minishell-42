/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:32:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/28 12:40:20 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/libft.h"
#include "init.h"

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
	ft_free(mini->env_copy);
	if (mini->message)
		free (mini->message);
}

int	init_struct(t_mini *mini, char *envp[])
{
	if (copy_env(mini, envp) == -1)
		return (-1);
	mini->message = NULL;
	return (0);
}
