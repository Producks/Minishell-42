/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:34:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/31 17:00:10 by ddemers          ###   ########.fr       */
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
		if (!ft_strncmp(mini->cmds_list->cmds[index], mini->env_copy[i], size)) // double check later fixed bug with length check
		{
			free(mini->env_copy[i]);
			if (flag)
				mini->env_copy[i] = ft_strjoin(mini->cmds_list->cmds[index], "\0");
			else
				mini->env_copy[i] = ft_strdup(mini->cmds_list->cmds[index]);
			return (1);
		}
		i++;
	}
	return (0);
}

/*Check for order later, adding it at the end for now*/
// static void	add_export(t_mini *mini, const char flag, int index)
// {
// 	char	**new;
// 	size_t	size;

// 	size = count_double_array(mini->env_copy);
// 	printf("%ld\n\n", size);
// 	new = ft_realloc(mini->env_copy, sizeof(char *) * (size + 1));
// 	//new = realloc(mini->env_copy, sizeof(char *) * (size + 1));
// 	if (!new)
// 		return ;
// 	if (flag)
// 		new[size - 1] = ft_strjoin(mini->cmds_list->cmds[index], "\0");
// 	else
// 		new[size - 1] = ft_strdup(mini->cmds_list->cmds[index]);
// 	new[size] = NULL;
// 	mini->env_copy = new;
// 	size = count_double_array(mini->env_copy);
// 	printf("%ld\n\n", size);
// }

static int	add_export(t_mini *mini, const char flag, int index)
{
	char	*str;
	int		ret;

    if (flag)
        str = ft_strjoin(mini->cmds_list->cmds[index], "\0");
    else
        str = ft_strdup(mini->cmds_list->cmds[index]);
	if (!str)
		return (FAILURE); // handle later
	ret = add_env_element(mini, str);
	if (ret == FAILURE)
		return (FAILURE);
	free (str);
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
	if (!mini->cmds_list->cmds[1])
		return (print_env(mini->env_copy));
	while (mini->cmds_list->cmds[++index])
	{
		ret = parse_string(mini->cmds_list->cmds[index]);
		if (ret == -1)
			continue ;
		else if (export_exist(mini, ret, index))
			continue ;
		add_export(mini, ret, index);
	}
	return (0);
}
