/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:34:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/04 08:49:50 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../main/struct.h"

static int	export_exist(t_mini *mini, const char flag, int index)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (mini->cmd[index][size] != '=')
		size++;
	while (mini->env_copy[i])
	{
		if (!ft_strncmp(mini->cmd[index], mini->env_copy[i], size))
		{
			free(mini->env_copy[i]);
			if (flag)
				mini->env_copy[i] = ft_strjoin(mini->cmd[index], "\0");
			else
				mini->env_copy[i] = ft_strdup(mini->cmd[index]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*Check for order later, adding it at the end for now*/
static void	add_export(t_mini *mini, const char flag, int index)
{
	char	**new;
	size_t	size;

	size = count_double_array(mini->env_copy);
	new = ft_realloc(mini->env_copy, sizeof(char *) * (size + 1));
	if (!new)
		return ;
	if (flag)
		new[size] = ft_strjoin(mini->cmd[index], "\0");
	else
		new[size] = ft_strdup(mini->cmd[index]);
	new[size + 1] = NULL;
	mini->env_copy = new;
	size = count_double_array(mini->env_copy);
}

static char	parse_string(const char *str)
{
	int	index;

	index = 0;
	if (!ft_isalpha(str[0]))
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
	if (!mini->cmd[1])
		return (print_env(mini->env_copy));
	while (mini->cmd[++index])
	{
		ret = parse_string(mini->cmd[index]);
		if (ret == -1)
			continue ;
		else if (export_exist(mini, ret, index))
			continue ;
		add_export(mini, ret, index);
	}
	return (0);
}
