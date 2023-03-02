/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:05 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 12:28:27 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/struct.h"

static void	ft_remove_elements(char **list, int index)
{
	int	i;
	int	null_count;
	int	size;
	char **new;

	size = 0;
	i = 0;
	null_count = 0;
	free(list[index]);
	list[index] = NULL;
	while (list[size])
		size++;
	new = malloc(sizeof(char *) * size);
	if (!new)
		return ;
	while (null_count != 2)
	{
		if (list[index] == NULL)
			null_count++;
		else
			new[i] = ft_strdup(list[i]);
		index++;
	}
	list = new; 
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
	while (mini->env_copy[index])
	{
		if (unset_strcmp(mini->cmd[1], mini->env_copy[index]))
		{
			ft_remove_elements(mini->env_copy, index);
			return (0);
		}
		index++;
	}
	return (0);
}
