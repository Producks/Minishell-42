/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:34:06 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 12:28:00 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../main/struct.h"

// /*Check for order later, adding it at the end for now
// ADD later parsing if first value is letter*/
// static void	add_export(t_mini *mini, const char flag, int index)
// {
// 	t_dlist	*node;
// 	int		i;

// 	i = 0;
// 	if (flag == -1)
// 		return ;
// 	while (mini->cmd[index][i] != '=')
// 		i++;
// 	node = create_node(ft_strdup(mini->cmd[index]));
// 	add_node(&mini->env_list, node);
// }

// static char	parse_string(const char *str)
// {
// 	int	index;

// 	index = 0;
// 	while (str[index] && str[index] != '=')
// 		index++;
// 	if (str[index] == '=')
// 	{
// 		if (str[index + 1] == '\0')
// 			return (1);
// 		return (0);
// 	}
// 	return (-1);
// }

// static int	print_env(t_mini *mini)
// {
// 	t_dlist *current;

// 	current = mini->env_list;
// 	while (current != NULL)
// 	{
// 		printf("declare -x %s\n", (char *)current->data);
// 		current = current->next;
// 	}
// 	return (0);
// }

int	ft_export(t_mini *mini)
{
	int		index;
	char	ret;

	index = 1;
	return (0);
	// if (mini->cmd[index] == NULL)
	// 	return (print_env(mini));
	// while (mini->cmd[index])
	// {
	// 	ret = parse_string(mini->cmd[index]);
	// 	add_export(mini, ret, index);
	// 	index++;
	// }
	// return (0);
}