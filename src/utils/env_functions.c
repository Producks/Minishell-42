/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:05:42 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 14:22:01 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	copy_env(t_mini *mini, char *envp[])
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

int	add_env_element(t_mini *mini, char *str_to_add)
{
	char	**new_envp;
	size_t	env_size;
	int		index;

	env_size = count_double_array(mini->env_copy);
	new_envp = malloc(sizeof(char *) * (env_size + 2));
	if (!new_envp)
		return (print_errno(ENOMEM), FAILURE);
	index = 0;
	while (index < env_size)
	{
		new_envp[index] = ft_strdup(mini->env_copy[index]);
		if (!new_envp[index])
			return (free_double_array(new_envp), print_errno(ENOMEM), FAILURE);
		index++;
	}
	new_envp[index] = ft_strdup(str_to_add);
	if (!new_envp[index])
		return (free_double_array(new_envp), print_errno(ENOMEM), FAILURE);
	index++;
	new_envp[index] = NULL;
	free_double_array(mini->env_copy);
	mini->env_copy = new_envp;
	return (SUCCESS);
}
