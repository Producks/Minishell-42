/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:05 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 15:51:11 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../main/struct.h"

static void	ft_remove_element(t_mini *mini, int index)
{
	int	i;
	int	size;
	char **new;

	size = 0;
	i = 0;
	while (mini->env_copy[size] != NULL)
		size++;
	new = malloc(sizeof(char *) * size);
	if (!new)
	{
		ft_free(mini->env_copy);
		mini->env_copy = NULL;
		return;
	}
	i = 0;
	while (mini->env_copy[i])
	{
		if (i == index)
			i++;
		else
		{
			new[i] = ft_strdup(mini->env_copy[i]);
			i++;
		}
	}
	//printf("%s\n", new[0]);
	new[i] = NULL;
	ft_free(mini->env_copy);
	for (int j = 0; new[j]; j++)
		printf("%d %s\n", j, new[j]);
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

	index = 0;
	if (mini->cmd[1] == NULL)
		return (0);
	while (mini->env_copy[index])
	{
		if (unset_strcmp(mini->cmd[1], mini->env_copy[index]) == 0)
		{
			ft_remove_element(mini, index);
			return (0);
		}
		index++;
	}
	for (int i = 0; mini->env_copy[i]; i++)
		printf("%s\n", mini->env_copy[i]);
	return (0);
}
