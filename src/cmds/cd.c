/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:34:58 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/30 22:50:50 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

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
			mini->env_copy[index] = ft_strjoin("PWD=", getcwd(NULL, 69));
			if (!mini->env_copy[index])
				return (-1);
			count++;
		}
		else if (ft_strncmp(mini->env_copy[index], "OLDPWD=", 7) == 0)
		{
			free(mini->env_copy[index]);
			mini->env_copy[index] = ft_strjoin("OLDPWD=", old_pwd); //protect this
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

static int	cd_deez(t_mini *mini, int count)
{
	char	*home;
	int		ret;

	if (count > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (0);
	}
	if (count > 1)
		ret = chdir(mini->cmds_list->cmds[1]);
	else
	{
		home = get_home(mini);
		if (!home)
			return (-1);
		ret = chdir(home);
	}
	return (ret);
}

int	cd(t_mini *mini)
{
	int		ret;
	int		count;
	char	*current;

	count = count_double_array(mini->cmds_list->cmds);
	current = getcwd(NULL, 69);
	if (!current)
		return (-1);
	ret = cd_deez(mini, count);
	if (ret == -1)
		perror("cd");
	ret = add_pwd_to_env(mini, current);
	if (ret)
		return (-1);
	free(current);
	return (0);
}
