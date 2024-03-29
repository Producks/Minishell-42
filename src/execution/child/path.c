/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:16:04 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 00:13:55 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*find_built_in_path(t_mini *mini)
{
	char	*path;
	char	**path_try;
	int		index;

	index = 0;
	while (mini->env_copy[index] && ft_strncmp(mini->env_copy[index],
			"PATH=", 5))
		index++;
	if (!mini->env_copy[index])
		return (NULL);
	path_try = ft_split(mini->env_copy[index], ':');
	if (!path_try)
		return (NULL);
	index = 0;
	while (path_try[index])
	{
		path = strjoin_path(path_try[index], mini->current_cmds[0], '/');
		if (!access(path, F_OK))
			return (free_double_array(path_try), path);
		free(path);
		index++;
	}
	free_double_array(path_try);
	return (NULL);
}

/*I CAN'T*/
char	*absolute_path(t_mini *mini)
{
	char	*absolute_path;

	if (!access(mini->current_cmds[0], F_OK))
	{
		absolute_path = ft_strdup(mini->current_cmds[0]);
		if (!absolute_path)
			return (print_errno(ENOMEM), NULL);
		return (absolute_path);
	}
	return (NULL);
}

char	*executable_path(t_mini *mini)
{
	char	*abs_path;
	char	*pwd;

	pwd = getcwd(NULL, 69);
	if (!pwd)
		return (NULL);
	abs_path = ft_strjoin(pwd, mini->current_cmds[0]);
	if (!abs_path)
		return (free (pwd), NULL);
	if (!access(mini->current_cmds[0], F_OK))
		return (abs_path);
	return (free(pwd), free(abs_path), NULL);
}

char	*find_path(t_mini *mini)
{
	char	*path;

	if (ft_strncmp(mini->current_cmds[0], "./", 2) == 0)
		path = absolute_path(mini);
	else if (ft_strncmp(mini->current_cmds[0], "/", 1) == 0)
		path = absolute_path(mini);
	else
		path = find_built_in_path(mini);
	return (path);
}
