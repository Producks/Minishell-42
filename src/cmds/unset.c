/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:05 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/05 12:37:34 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../main/struct.h"

// extern int	g_exit_status;

static void	ft_remove_element(t_mini *mini, int index, int i, int j)
{
	int		size;
	char	**new;

	size = 0;
	while (mini->env_copy[size] != NULL)
		size++;
	new = malloc(sizeof(char *) * size);
	if (!new)
	{
		ft_free(mini->env_copy);
		mini->env_copy = NULL;
		return ;
	}
	while (mini->env_copy[++i])
		if (i != index)
			new[j++] = ft_strdup(mini->env_copy[i]);
	new[j] = NULL;
	ft_free(mini->env_copy);
	mini->env_copy = new;
}

static int	unset_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
		if (*str1++ != *str2++)
			return (1);
	if (!*str1 && *str2 == '=')
		return (0);
	return (1);
}

/*More testing need to be done, seems to be good for now*/
int	unset(t_mini *mini)
{
	int	index;
	int	j;

	j = 0;
	if (mini->cmd[1] == NULL)
		return (0);
	while (mini->cmd[++j])
	{
		index = 0;
		while (mini->env_copy[index])
		{
			if (unset_strcmp(mini->cmd[j], mini->env_copy[index]) == 0)
			{
				ft_remove_element(mini, index, -1, 0);
				break ;
			}
			index++;
		}
	}
	return (0);
}
