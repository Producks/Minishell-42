/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:21:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 00:21:54 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

static void	ft_remove_element(t_mini *mini, int index, int i, int j)
{
	int		size;
	char	**new;

	size = 0;
	while (mini->env_copy[size] != NULL)
		size++;
	new = malloc(sizeof(char *) * size);
	if (!new)
	{
		free_double_array(mini->env_copy);
		mini->env_copy = NULL;
		return ;
	}
	while (mini->env_copy[++i])
		if (i != index)
			new[j++] = ft_strdup(mini->env_copy[i]);
	new[j] = NULL;
	free_double_array(mini->env_copy);
	mini->env_copy = new;
}

static int	unset_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
		if (*str1++ != *str2++)
			return (1);
	if (!*str1 && *str2 == '=')
		return (0);
	return (1);
}

static void	write_unset_error(const char *str)
{
	write(STDERR_FILENO, "Minishell: unset: `", 19);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifiter\n", 27);
}

static int	check_syntax_error_unset(const char *str, char c)
{
	if (!ft_isalpha(c) && c != '_')
	{
		write_unset_error(str);
		return (1);
	}
	return (0);
}

int	unset(t_mini *mini)
{
	int	index;
	int	j;

	j = 0;
	if (mini->current_cmds[1] == NULL)
		return (SUCCESS);
	while (mini->current_cmds[++j])
	{
		if (check_syntax_error_unset(mini->current_cmds[j],
				mini->current_cmds[j][0]))
			continue ;
		index = 0;
		while (mini->env_copy[index])
		{
			if (unset_strcmp(mini->current_cmds[j],
					mini->env_copy[index]) == 0)
			{
				ft_remove_element(mini, index, -1, 0);
				break ;
			}
			index++;
		}
	}
	return (SUCCESS);
}
