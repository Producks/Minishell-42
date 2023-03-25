/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_christo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:59:33 by cperron           #+#    #+#             */
/*   Updated: 2023/03/24 23:19:02 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

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
int	is_pipe(char *token)
{
	if (token[0] == '|')
		return (1);
	return (0);
}

int is_redir_2(char *token)
{
	if (token[0] == '<' || token[0] == '>')
		return (1);
	return (0);
}

// return 1 if token is a redir else return 0
int is_redir(char *token)
{
	if (token[0] == '<' || token[0] == '>' || token[0] == '|')
		return (1);
	return (0);
}

int 	count_cmds_arg(char **tokens, int i)
{
	int n;

	n = 0;
	while (tokens[i] && is_redir(tokens[i]) == 0)
	{
		n++;
		i++;
	}
	printf("nb arg: %d\n", n);
	return (n);
}

int	addnode_end_cmds(t_cmds **list, char **tokens, int i)
{
	t_cmds *new_node;
	int n;
	int c;
	
	c = 0;
	new_node = ft_calloc(1, sizeof(t_cmds));
	n = count_cmds_arg(tokens, i);
	printf("i: %d\n", i);
	printf("n: %d\n", n);
	new_node->cmds = ft_calloc(n + 1, sizeof(char*));
	if (is_redir(tokens[i]) == 1)
	{
		// puts("ici");
		i++;
	}
	while (tokens[i] && is_redir(tokens[i]) == 0)
	{
		interpret_quotes(NULL, tokens, i);
		new_node->cmds[c] = ft_strdup(tokens[i]);
		if (c == 0)
			printf(YEL "cmds : %s\n" RESET, new_node->cmds[c]);
		else
			printf("arg : %s\n", new_node->cmds[c]);
		c++;
		i++;
	}
	new_node->cmds[c] = NULL;
	new_node->next = NULL;
	printf("arg : %s\n", new_node->cmds[c]);
	printf("n: %d\n", n);
	redir_list_2(list, tokens, i, n, 1);
	addnodecmds(list, new_node);
	return (i);
}

int 	count_cmds_arg_first(char **tokens, int i)
{
	int n;
	int max;

	n = 0;
	max = i;
	// i = 0;
	while (is_redir(tokens[i]) == 1)
		i += 2;
	while (tokens[i] && is_redir(tokens[i]) == 0)
	{
		n++;
		i++;
	}
	// while (tokens[i] && i < max)
	// {
	// 	if (is_redir(tokens[i]) == 0)
	// 		n++;
	// 	i++;
	// }
	// n++;
	printf("nb arg: %d\n", n);
	return (n);
}

int	addnode_end_cmds_first(t_cmds **list, char **tokens, int i)
{
	t_cmds *new_node;
	int n;
	int c;
	
	c = 0;
	new_node = ft_calloc(1, sizeof(t_cmds));
	n = count_cmds_arg_first(tokens, i);
	new_node->cmds = ft_calloc(sizeof(char*), n + 1);

	
	while (is_redir(tokens[i]) == 1)
		i += 2;
	interpret_quotes(NULL, tokens, i);
	new_node->cmds[c] = ft_strdup(tokens[i]);
	printf(YEL "cmds : %s\n" RESET, new_node->cmds[c]);
	c++;
	i++;
	// i = 0;
	while (tokens[i] && n > 1)
	{
		if (is_redir(tokens[i]) == 1)
			i++;
		interpret_quotes(NULL, tokens, i);
		new_node->cmds[c] = ft_strdup(tokens[i]);
		printf("arg : %s\n", new_node->cmds[c]);
		c++;
		i++;
		n--;
	}
	// printf("THE i: %d\n", i);
	n--;
	new_node->cmds[c] = NULL;
	new_node->next = NULL;
	printf("larg : %s\n", new_node->cmds[c]);
	printf("n: %d\n", n);
	redir_list_2(list, tokens, i, n, 0);
	addnodecmds(list, new_node);
	return (i);
}



void	check_cmds(t_cmds **cmds, char **tokens, int num_token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (is_redir(tokens[i]) == 1 && i == 0)
		{
			i +=2 ;
			i = addnode_end_cmds_first(cmds, tokens, i);
			if (is_redir(tokens[i]) == 1)
				i++;
		}
		else
		{
			while (is_redir(tokens[i]) == 1)
			{

				i+=2;
			}
			i = addnode_end_cmds(cmds, tokens, i);
			printf("THE i: %d\n", i);
			if (!tokens[i])
				break;
			while (is_redir(tokens[i]) == 1)
			{
				i+=2;
				if (!tokens[i])
				break;
			}
		}
		if (!tokens[i])
			break;
		// i += 2;
	}
	
}

void	parse_linked_list(t_mini *mini, char **tokens)
{
	t_cmds	*cmds;
	
	cmds = NULL;
	// print_token(tokens);
	check_cmds(&cmds, tokens, 0);
	
	// mini->cmds_list = cmds;
	cmds = free_linked_list_cmds(&cmds);
	// redir_list(tokens);
	// print_cmds_list(cmds);
}
