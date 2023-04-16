/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:34:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/12 15:35:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static char	export_exist(t_mini *mini, const char flag, int index)
{
	int		i;
	char	*str;
	size_t	size;

	i = 0;
	while (mini->env_copy[i])
	{
		size = 0;
		while (mini->env_copy[i][size] != '=')
			size++;
		if (!ft_strncmp(mini->current_cmds[index], mini->env_copy[i], size))
		{
			if (flag)
				str = ft_strjoin(mini->current_cmds[index], "\0");
			else
				str = ft_strdup(mini->current_cmds[index]);
			if (!str)
				return (print_errno(ENOMEM), FAILURE);
			free(mini->env_copy[i]);
			mini->env_copy[i] = str;
			return (1);
		}
		i++;
	}
	return (0);
}

static char	parse_string(const char *str, bool *error)
{
	int	index;

	index = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		write(2, "minishell: export: `", 21);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 27);
		*error = true;
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
		return (BUILTIN_SUCCESS);
	while (*env)
		printf("declare -x \"%s\"\n", *env++);
	return (BUILTIN_SUCCESS);
}

int	ft_export(t_mini *mini)
{
	bool	error;
	int		index;
	char	ret;

	index = 0;
	if (!mini->current_cmds[1])
		return (print_env(mini->env_copy));
	error = false;
	while (mini->current_cmds[++index])
	{
		ret = parse_string(mini->current_cmds[index], &error);
		if (ret == FAILURE)
			continue ;
		ret = export_exist(mini, ret, index);
		if (ret == FAILURE)
			return (ENOMEM);
		if (ret)
			continue ;
		if (add_env_element(mini, mini->current_cmds[index]))
			return (ENOMEM);
	}
	if (error == true)
		return (BUILTIN_COMMAND_ERROR);
	return (BUILTIN_SUCCESS);
}
