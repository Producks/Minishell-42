/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linked_list_exec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:07:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/12 11:02:38 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	free_double_array_execve(char **str, char **nope)
{
	int	index;

	index = 0;
	if (!str || !nope)
		return ;
	if (str == nope)
		return ;
	while (str[index])
		free(str[index++]);
	free (str);
}

void	free_linked_list_execve(t_mini *mini)
{
	t_cmds	*previous;

	previous = NULL;
	while (mini->head_cmd)
	{
		if (mini->head_cmd->redir_list)
			clean_redir_list(mini->head_cmd);
		free_double_array_execve(mini->head_cmd->cmds, mini->current_cmds);
		previous = mini->head_cmd;
		mini->head_cmd = mini->head_cmd->next;
		free(previous);
		previous = NULL;
	}
}
