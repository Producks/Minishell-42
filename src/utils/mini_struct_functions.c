/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:32:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 23:59:06 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*safe_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

void	clean_redir_list(t_cmds *current)
{
	t_redir	*head;

	head = current->redir_list;
	while (current->redir_list)
	{
		head = current->redir_list->next;
		if (current->redir_list->filename != NULL)
			free(current->redir_list->filename);
		if (current->redir_list->tmp_file != NULL)
			free(current->redir_list->tmp_file);
		free(current->redir_list);
		current->redir_list = head;
	}
}

void	*free_linked_list_mini(t_cmds **head)
{
	t_cmds	*current;
	t_cmds	*previous;

	current = *head;
	while (current)
	{
		if (current->redir_list)
			clean_redir_list(current);
		free_double_array(current->cmds);
		previous = current;
		current = current->next;
		free(previous);
		previous = NULL;
	}
	return (NULL);
}

void	free_struct_mini(t_mini *mini)
{
	mini->env_copy = free_double_array(mini->env_copy);
	mini->current_cmds = free_double_array(mini->current_cmds);
	if (mini->message)
		free (mini->message);
	if (mini->current_dir)
		free (mini->current_dir);
	close(mini->fd_in);
	close(mini->fd_out);
}

int	init_struct_mini(t_mini *mini, char *envp[])
{
	mini->current_dir = getcwd(NULL, 0);
	if (!mini->current_dir)
		return (print_errno(errno), FAILURE);
	if (copy_env(mini, envp) == FAILURE)
		return (free(mini->current_dir), FAILURE);
	mini->message = NULL;
	mini->cmds_list = NULL;
	mini->current_cmds = NULL;
	mini->head_cmd = NULL;
	mini->is_one_cmd = false;
	mini->skip_waiting = false;
	mini->exit = false;
	mini->fd_in = dup(STDIN_FILENO);
	mini->fd_out = dup(STDOUT_FILENO);
	return (SUCCESS);
}
