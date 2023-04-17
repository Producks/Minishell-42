/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:34:58 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 00:13:38 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static char	*get_home(t_mini *mini)
{
	int		index;
	char	*copy;

	index = 0;
	while (mini->env_copy[index] != NULL)
	{
		if (ft_strncmp(mini->env_copy[index], "HOME=", 5) == 0)
		{
			copy = ft_strdup(mini->env_copy[index] + 5);
			if (!copy)
				return (print_errno(ENOMEM), NULL);
			if (!copy[0])
				return (free(copy), NULL);
			return (copy);
		}
		index++;
	}
	write(2, "Minishell: cd: HOME not set\n", 28);
	return (NULL);
}

static int	cd_deez(t_mini *mini, int count)
{
	char	*home;

	if (count > 1)
	{
		if (chdir(mini->current_cmds[1]) == FAILURE)
			return (print_errno(errno), BUILTIN_COMMAND_ERROR);
		return (SUCCESS);
	}
	home = get_home(mini);
	if (!home)
		return (BUILTIN_COMMAND_ERROR);
	if (chdir(home) == FAILURE)
		return (free(home), BUILTIN_COMMAND_ERROR);
	return (BUILTIN_SUCCESS);
}

char	*get_current_dir(t_mini *mini)
{
	char	*dir;

	if (!mini->current_dir)
	{
		dir = getcwd(NULL, 0);
		if (!dir)
			return (print_errno(errno), NULL);
	}
	dir = ft_strdup(mini->current_dir);
	if (!dir)
		return (print_errno(errno), NULL);
	return (dir);
}

void	update_pwd(t_mini *mini)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		write(STDERR_FILENO, "Minishell: Couldn't update directoy\n", 36);
		return ;
	}
	free(mini->current_dir);
	mini->current_dir = current_pwd;
}

int	cd(t_mini *mini)
{
	size_t	argument_count;
	int		ret;
	char	*new_dir;
	char	*current_dir;

	argument_count = count_double_array(mini->current_cmds);
	if (argument_count > 2)
	{
		write(STDERR_FILENO, "Minishell: cd: too many arguments\n", 34);
		return (BUILTIN_COMMAND_ERROR);
	}
	current_dir = get_current_dir(mini);
	if (!current_dir)
		return (BUILTIN_COMMAND_ERROR);
	if (cd_deez(mini, argument_count) == FAILURE)
		return (free(current_dir), BUILTIN_COMMAND_ERROR);
	update_pwd(mini);
	if (add_pwd_to_env(mini, current_dir, 0, 0) == FAILURE)
		return (free(current_dir), ENOMEM);
	free(current_dir);
	return (BUILTIN_SUCCESS);
}
