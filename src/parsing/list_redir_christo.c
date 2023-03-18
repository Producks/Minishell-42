/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redir_christo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:45:03 by cperron           #+#    #+#             */
/*   Updated: 2023/03/17 23:41:04 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*free_linked_list_redirr(t_redir **head)
{
	t_redir *current;
	t_redir *previous;
	
	current = *head;
	while (current)
	{
		previous = current;
		current = current->next;
		free(previous);
		previous = NULL;
	}
	return (NULL);
}

void	print_redir_list(t_redir *redir)
{
	t_redir *current;
	int i;
	
	i = 1;
	current = redir;
	while (current)
	{
		if (current->type == 50)
			printf("|\n");
		if (current->type == 51)
			printf(">\n");
		if (current->type == 52)
			printf("<\n");
		if (current->type == 53)
			printf(">>\n");
		if (current->type == 54)
			printf("<<\n");
		printf("node :%d\n", i);
		printf("in :%d\n", current->in);
		printf("out :%d\n", current->out);
		printf("filename : %s\n\n", current->filename);
		current = current->next;
		i++;
	}
}

void	addnode_end_redir(t_redir **list, int type, int dir, char *filename)
{
	t_redir *new_node;
	
	new_node = ft_calloc(1, sizeof(t_redir));
	new_node->type = type;
	if (dir == 1)
		new_node->out = true;
	if (dir == 0)
		new_node->in = true;
	new_node->filename = filename;
	new_node->next = NULL;
	new_node->head = *list;


	t_redir *current;
	
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

void	check_pipe(t_redir **redir, char **tokens, int num_token)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			addnode_end_redir(redir, 50, 1, tokens[i - 1]);
			addnode_end_redir(redir, 50, 0, tokens[i + 1]);
		}	
		i++;
	}
}

void	check_redir(t_redir **redir, char **tokens, int num_token)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
			addnode_end_redir(redir, 51, 1, tokens[i + 1]);
		if (ft_strcmp(tokens[i], "<") == 0)
			addnode_end_redir(redir, 52, 0, tokens[i + 1]);
		if (ft_strcmp(tokens[i], ">>") == 0)
			addnode_end_redir(redir, 53, 1, tokens[i + 1]);
		if (ft_strcmp(tokens[i], "<<") == 0)
			addnode_end_redir(redir, 54, 0, tokens[i + 1]);
		i++;
	}
}

void	redir_list(char **tokens)
{
	t_redir *redir;
	
	redir = NULL;
	check_pipe(&redir, tokens, 0);
	check_redir(&redir, tokens, 0);
	print_redir_list(redir);
	if(redir)
		redir = free_linked_list_redirr(&redir);
	print_redir_list(redir);
}
