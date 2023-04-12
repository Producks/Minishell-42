/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:34:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 21:45:12 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static int	export_exist(t_mini *mini, const char flag, int index)
{
	int		i;
	size_t	size;

	i = 0;
	while (mini->env_copy[i])
	{
		size = 0;
		while (mini->env_copy[i][size] != '=')
			size++;
		if (!ft_strncmp(mini->current_cmds[index], mini->env_copy[i], size))
		{
			free(mini->env_copy[i]);
			if (flag)
				mini->env_copy[i] = ft_strjoin(mini->current_cmds[index], "\0"); // fix
			else
				mini->env_copy[i] = ft_strdup(mini->current_cmds[index]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_export(t_mini *mini, const char flag, int index)
{
	char	*str;
	int		ret;

	if (flag)
		str = ft_strjoin(mini->current_cmds[index], "\0");
	else
		str = ft_strdup(mini->current_cmds[index]);
	if (!str)
		return (FAILURE); // handle later
	ret = add_env_element(mini, str);
	if (ret == FAILURE)
		return (FAILURE);
	free (str);
	return (SUCCESS);
}

static char	parse_string(const char *str)
{
	int	index;

	index = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		write(2, "minishell: export: '", 21);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 27);
		return (-1);
	}
	while (str[index] && str[index] != '=')
		index++;
	if (str[index] == '=')
	{
		if (str[index + 1] == '\0')
			return (1);
		return (0);
	}
	return (-1);
}

static int	print_env(char **env)
{
	if (!env)
		return (0);
	while (*env)
		printf("declare -x %s\n", *env++);
	return (0);
}

int	ft_export(t_mini *mini)
{
	int		index;
	char	ret;

	index = 0;
	if (!mini->current_cmds[1])
		return (print_env(mini->env_copy));
	while (mini->current_cmds[++index])
	{
		ret = parse_string(mini->current_cmds[index]);
		if (ret == -1)
			continue ;
		else if (export_exist(mini, ret, index))
			continue ;
		add_export(mini, ret, index);
	}
	return (0);
}
