/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:34:58 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 16:26:52 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static int	add_pwd_to_env(t_mini *mini, char *old_pwd, int index, int count)
{
	char	*copy;

	while (mini->env_copy[index] && count != 2)
	{
		if (ft_strncmp(mini->env_copy[index], "PWD=", 4) == 0)
		{
			copy = ft_strjoin("PWD=", getcwd(NULL, 69));
			if (!copy)
				return (print_errno(ENOMEM), FAILURE);
			free(mini->env_copy[index]);
			mini->env_copy[index] = copy;
			count++;
		}
		else if (ft_strncmp(mini->env_copy[index], "OLDPWD=", 7) == 0)
		{
			copy = ft_strjoin("OLDPWD=", old_pwd);
			if (!copy)
				return (print_errno(ENOMEM), FAILURE);
			free(mini->env_copy[index]);
			mini->env_copy[index] = copy;
			count++;
		}
		index++;
	}
	return (SUCCESS);
}

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
	int		ret;

	if (count > 1)
		ret = chdir(mini->current_cmds[1]);
	else
	{
		home = get_home(mini);
		if (!home)
			return (ENOMEM);
		ret = chdir(home);
	}
	if (ret == FAILURE)
	{
		print_errno(errno);
		return (BUILTIN_COMMAND_ERROR);
	}
	return (SUCCESS);
}

int	cd(t_mini *mini)
{
	int		ret;
	int		count;
	char	*current;

	count = count_double_array(mini->current_cmds);
	current = getcwd(NULL, 69);
	if (!current)
		return (print_errno(errno), errno);
	ret = cd_deez(mini, count);
	if (ret != SUCCESS)
		return (ret);
	ret = add_pwd_to_env(mini, current, 0, 0);
	if (ret == FAILURE)
		return (ENOMEM);
	free(current);
	return (BUILTIN_SUCCESS);
}
