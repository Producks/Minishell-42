/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redir_christo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:45:03 by cperron           #+#    #+#             */
/*   Updated: 2023/03/27 18:58:03 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	*free_linked_list_redirr(t_redir **head)
// {
// 	t_redir *current;
// 	t_redir *previous;
	
// 	current = *head;
// 	while (current)
// 	{
// 		previous = current;
// 		current = current->next;
// 		free(previous);
// 		previous = NULL;
// 	}
// 	return (NULL);
// }

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

	addnoderedir(list, new_node);
	// new_node->next = NULL;
	// new_node->head = *list;
	// t_redir *current;
	
	// if (*list == NULL)
	// 	*list = new_node;
	// else
	// {
	// current = *list;
	// while(current->next)
	// 	current = current->next;
	// current->next = new_node;
	// }
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

int	check_redir_2(t_redir **redir, char **tokens, int i, int bef_cmd)
{
	int	max;
	
	max = i;
	i = bef_cmd;
	while (tokens[i] && is_pipe(tokens[i]) == 0)
	{
		
		// if (is_redir(tokens[i + 2]) == 0) // a checker
		// {
		// 	// i++;
		// 	break;
		// }
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
	// print_redir_list(*redir);
	// printf ("THE i: %d\n", i);
	if (!tokens[i]) // a checker
		i -= 2;
	return (i);
}

int	redir_list_3(t_cmds *new_node, char **tokens, int i, int bef_cmd)
{
	t_redir *redir;
	
	redir = NULL;
	i = bef_cmd;
	check_pipe_in(&redir, tokens, i, 0);
	check_pipe_out(&redir, tokens, i);
	i = check_redir_2(&redir, tokens, i, bef_cmd);
	// printf ("THE i: %d\n", i);
	// print_redir_list(redir);
	new_node->redir_list = redir;
	// if(redir)
	// 	redir = free_linked_list_redirr(&redir);
	// print_redir_list(redir);
	return (i);
}
