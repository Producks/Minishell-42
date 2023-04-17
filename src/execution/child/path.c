/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:16:04 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 00:11:10 by ddemers          ###   ########.fr       */
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
	path_try = ft_split((mini->env_copy[index] + 5), ':');
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

/* I CAN'T */
char	*absolute_path(char *path)
{
	char	*absolute_path;

	if (!access(path, F_OK))
	{
		absolute_path = ft_strdup(path);
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

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	abs_path = ft_strjoin(pwd, mini->current_cmds[0]);
	if (!abs_path)
		return (free (pwd), NULL);
	if (!access(mini->current_cmds[0], F_OK))
		return (abs_path);
	return (free(pwd), free(abs_path), NULL);
}

char	*change_path(t_mini *mini)
{
	char	*ret;
	char	*dir;
	int		count;
	int		index;

	count = count_double_dot(mini->current_cmds[0]);
	if (count == 0)
	{
		ret = ft_strdup(mini->current_cmds[0]);
		if (!ret)
			return (print_errno(errno), NULL);
		return (ret);
	}
	index = (3 * count);
	dir = get_dir_changed(mini, count);
	if (!dir)
		return (NULL);
	ret = strjoin_path(dir, (mini->current_cmds[0] + index), '/');
	return (free(dir), ret);
}

char	*find_path(t_mini *mini)
{
	char	*path;
	char	*path_changed;

	path_changed = change_path(mini);
	if (!path_changed)
		return (NULL);
	if (ft_strncmp(path_changed, "./", 2) == 0)
		path = absolute_path(path_changed);
	else if (ft_strncmp(path_changed, "/", 1) == 0)
		path = absolute_path(path_changed);
	else
		path = find_built_in_path(mini);
	free(path_changed);
	return (path);
}
