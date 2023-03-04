/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:34:58 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/04 15:16:07 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	add_pwd_to_env(t_mini *mini, char *old_pwd)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (mini->env_copy[index] && count != 2)
	{
		if (ft_strncmp(mini->env_copy[index], "PWD=", 4) == 0)
		{
			free(mini->env_copy[index]);
			count++;
		}
		else if (ft_strncmp(mini->env_copy[index], "OLDPWD=", 7) == 0)
		{
			free(mini->env_copy[index]);
			count++;
		}
		index++;
	}
	return (0);
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
				return (NULL);
			if (!copy[0])
				return (free(copy), NULL);
			return (copy);
		}
		index++;
	}
	write(2, "minishell: cd: HOME not set\n", 28);
	return (NULL);
}

int	cd(t_mini *mini)
{
	int		ret;
	int		count;
	char	*error;
	char	*home;
	char	*current;
	
	count = count_double_array(mini->cmd);
	current = getcwd(NULL, 69);
	if (count > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (0);
	}
	if (count > 1)
		ret = chdir(mini->cmd[1]);
	else
	{
		home = get_home(mini);
		if (!home)
			return (-1);
		ret = chdir(home);
	}
	if (ret == -1)
		perror("cd");
	add_pwd_to_env(mini, current);
	return (0);
}
