/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_christo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:59:33 by cperron           #+#    #+#             */
/*   Updated: 2023/03/17 23:40:31 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*free_linked_list_cmds(t_cmds **head)
{
	t_cmds *current;
	t_cmds *previous;
	
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

// void	print_cmds_list(t_redir *cmds)
// {
// 	t_redir *current;
// 	int i;
	
// 	i = 1;
// 	current = cmds;
// 	while (current)
// 	{
	
// 		current = current->next;
// 	}
// }


void	addnode_end_cmds(t_cmds **list, char *cmds, char ** tokens)
{
	t_cmds *new_node;
	t_cmds *current;
	
	new_node = ft_calloc(1, sizeof(t_redir));
	if (ft_strcmp(cmds, "echo") == 0)
		printf("echo\n");
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

void	check_cmds(t_cmds **cmds, char **tokens, int num_token)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "echo") == 0)
			addnode_end_cmds(cmds, "echo", tokens);
		// else if (ft_strcmp(tokens[i], "cd") == 0)
		// 	cd(mini);
		// else if (ft_strcmp(tokens[i], "pwd") == 0)
		// 	pwd();
		// else if (ft_strcmp(tokens[i], "export") == 0)
		// 	ft_export(mini);
		// else if (ft_strcmp(tokens[i], "unset") == 0)
		// 	unset(mini);
		// else if (ft_strcmp(tokens[i], "env") == 0)
		// 	env(mini->env_copy);
		i++;
	}
}

void	parse_linked_list(char **tokens, int num_token)
{
	t_cmds	*cmds;
	
	cmds = NULL;
	redir_list(tokens);
	// check_cmds(&cmds, tokens, 0);
	// cmds = free_linked_list_cmds(&cmds);
	
	
	
	// addnode_end_redir(&redir, 1, 1);
	// addnode_end_redir(&redir, 2, 1);
	// addnode_end_redir(&redir, 3, 0);
	// addnode_end_redir(&redir, 4, 0);
	// print_cmds_list(cmds);;
}
