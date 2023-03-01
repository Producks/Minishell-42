/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:05 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/01 13:01:03 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct.h"

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
	t_dlist	*current;

	current = mini->env_list;
	while (current)
	{
		if (unset_strcmp(mini->cmd[1], (char *)current->data) == 0)
		{
			delete_node(&mini->env_list, current);
			return (0);
		}
		current = current->next;
	}
	return (0);
}