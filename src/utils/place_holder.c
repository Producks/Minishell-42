/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_holder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:17:30 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/17 15:57:56 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*typedef struct s_redirect
{
    char				*filename;
    int					type;
    struct s_redirect	*next;
}	t_redir;
*/

#include "utils.h"

t_redir *create_node_redir(void)
{
	t_redir *new_node;

		new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
		return (NULL);
	return (new_node);
}

void	add_node_redir(t_redir **head, t_redir *new_node)
{
	t_redir *current;

	if (!*head)
		return ;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
		// new_node->next = NULL;
	}
}

void	delete_node_redir(t_redir **head, t_redir *node_to_delete)
{
	t_redir	*previous;
	t_redir	*current;
	
	if (node_to_delete == NULL || *head == NULL)
		return;
	if (*head == node_to_delete)
	{
		*head = node_to_delete->next;
		free(node_to_delete->filename);
		free(node_to_delete);
		return;
    }
    previous = *head;
    current = previous->next;
	while (current)
	{
		if (current == node_to_delete)
		{
			previous->next = current->next;
			free(current->filename);
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}


void	*free_linked_list_redir(t_redir **head)
{
	t_redir	*current;
	t_redir	*previous;

	current = *head;
	while (current)
	{
		free(current->filename);
		previous = current;
		current = current->next;
		free (previous);
		previous = NULL;
	}
	return (NULL);
}
