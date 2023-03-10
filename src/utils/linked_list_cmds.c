/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:06:40 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/10 12:36:59 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"
#include "../../libs/Libft/libft.h"

t_cmds *create_node_cmds(void)
{
	t_cmds *new_node;

	new_node = ft_calloc(1, sizeof(t_cmds));
	if (!new_node)
		return (NULL);
	return (new_node);
}

void	add_node_cmds(t_cmds **head, t_cmds *new_node)
{
	t_cmds *current;

	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
	}
}

void *safe_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

void	delete_node_cmds(t_cmds **head, t_cmds *node_to_delete)
{
	if (*head == node_to_delete)
		*head = node_to_delete->next;
	if (node_to_delete->previous != NULL)
		node_to_delete->previous->next = node_to_delete->next;
	if (node_to_delete->next != NULL)
		node_to_delete->next->previous = node_to_delete->previous;
	ft_free(node_to_delete->cmds);
	node_to_delete->path = safe_free(node_to_delete->path);
	node_to_delete->infile = safe_free(node_to_delete->infile);
	node_to_delete->outfile = safe_free(node_to_delete->outfile);
	free (node_to_delete);
}


void	*free_linked_list_mini(t_cmds **head)
{
	t_cmds *current;
	t_cmds *previous;
	
	current = *head;
	while (current)
	{
		ft_free(current->cmds);
		safe_free(current->path);
		safe_free(current->infile);
		safe_free(current->outfile);
		previous = current;
		current = current->next;
		free(previous);
		previous = NULL;
	}
	return (NULL);
}
