/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:06:40 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/06 12:12:01 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"
#include "../../libs/Libft/libft.h"

t_cmds *create_node_cmds(void)
{
	t_cmds *new_node;

	new_node = malloc(sizeof(t_cmds));
	if (!new_node)
		return (NULL);
	new_node->cmds = NULL;
	new_node->path = NULL;
	new_node->in = 0;
	new_node->out = 0;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->previous = NULL;
	new_node->next = NULL;
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
