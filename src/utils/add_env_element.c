/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:36:27 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/10 10:03:18 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	add_env_element(t_mini *mini, char *str_to_add)
{
	char	**new_envp;
	size_t	env_size;
	int		index;

	env_size = count_double_array(mini->env_copy);
	new_envp = malloc(sizeof(char *) * (env_size + 2));
	if (!new_envp)
		return (FAILURE);
	index = 0;
	while (index < env_size)
	{
		new_envp[index] = ft_strdup(mini->env_copy[index]);
		if (!new_envp[index])
		{
			free_double_array(new_envp);
			return (FAILURE); // add later
		}
		index++;
	}
	new_envp[index] = ft_strdup(str_to_add);
	if (!new_envp[index])
	{
		free_double_array(new_envp);
		return (FAILURE); // add later
	}
	index++;
    new_envp[index] = NULL;
    free_double_array(mini->env_copy);
    mini->env_copy = new_envp;
    return (SUCCESS);
}
