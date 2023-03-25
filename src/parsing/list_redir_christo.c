/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redir_christo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:45:03 by cperron           #+#    #+#             */
/*   Updated: 2023/03/24 21:13:56 by cperron          ###   ########.fr       */
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
		printf(GRN "node :%d\n" RESET, i);
		printf("in :%d\n", current->in);
		printf("out :%d\n", current->out);
		printf("filename : %s\n\n", current->filename);
		printf("next : %p\n", current->next);
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

int	check_pipe_in(t_redir **redir, char **tokens, int i, int n)
{
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			// puts("ici");
			addnode_end_redir(redir, 50, 1, NULL);
			// print_redir_list(*redir);
			return (1);
		}	
		i++;
	}
	return (0);
}

int	check_pipe_out(t_redir **redir, char **tokens, int i)
{
	int j;

	j = 0;
	while (tokens[j] && j < i)
	{
		if (ft_strcmp(tokens[j], "|") == 0)
		{
			addnode_end_redir(redir, 50, 0, NULL);
			// print_redir_list(*redir);
			return (1);
		}	
		j++;
	}
	return (0);
}

void	check_redir(t_redir **redir, char **tokens, int i)
{
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
	print_redir_list(*redir);
}

void	check_redir_first(t_redir **redir, char **tokens, int i, int n)
{
	while (tokens[i] && i < n)
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
	print_redir_list(*redir);
}

void	redir_list_2(t_cmds **cmds, char **tokens, int i, int n, int f)
{
	t_redir *redir;
	
	redir = NULL;
	
	check_pipe_in(&redir, tokens, i, n);

	check_pipe_out(&redir, tokens, i);
	if (f == 1)
		check_redir(&redir, tokens, i);
	if (f == 0)
		check_redir_first(&redir, tokens, 0, i);
	// print_redir_list(redir);
	if(redir)
		redir = free_linked_list_redirr(&redir);
	// print_redir_list(redir);
}

// void	redir_list(char **tokens)
// {
// 	t_redir *redir;
	
// 	redir = NULL;
// 	check_pipe(&redir, tokens, 0);
// 	check_redir(&redir, tokens, 0);
// 	print_redir_list(redir);
// 	if(redir)
// 		redir = free_linked_list_redirr(&redir);
// 	print_redir_list(redir);
// }
