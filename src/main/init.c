/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:32:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 13:53:01 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../lib/libft.h"
#include "init.h"

static int	copy_env_list(t_mini *mini, char *envp[])
{
	t_dlist	*head;
	t_dlist	*node;

	head = mini->env_list;
	while (*envp)
	{
		node = create_node(ft_strdup(*envp));
		if (!node || !node->data)
		{
			free_linked_list(&mini->env_list);
			return (-1);
		}
		if (head == NULL)
		{
			head = node;
			mini->env_list = head;
		}
		else
			add_node(&head, node);
		envp++;
	}
	return (0);
}

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
	free_linked_list(&mini->env_list);
	if (mini->message)
		free (mini->message);
}

int	init_struct(t_mini *mini, char *envp[])
{
	mini->env_list = NULL;
	if (copy_env(mini, envp) == -1)
		return (-1);
	copy_env_list(mini, envp);
	mini->message = NULL;
	return (0);
}
