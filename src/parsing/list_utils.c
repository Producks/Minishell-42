/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:18:42 by cperron           #+#    #+#             */
/*   Updated: 2023/04/01 18:26:24 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void addnodecmds(t_cmds **list, t_cmds *new_node)
{
	t_cmds *current;
	
	new_node->head = *list;
	if (*list == NULL)
		*list = new_node;
	else
	{
		current = *list;
		while(current->next)
			current = current->next;
		current->next = new_node;
	}
	
}

void addnoderedir(t_redir **list, t_redir *new_node)
{
	t_redir *current;
	
	new_node->next = NULL;
	new_node->head = *list;
	if (*list == NULL)
		*list = new_node;
	else
	{
		current = *list;
		while(current->next)
			current = current->next;
		current->next = new_node;
	}
}
