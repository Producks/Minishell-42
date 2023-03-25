/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_christo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:59:33 by cperron           #+#    #+#             */
/*   Updated: 2023/03/25 01:52:39 by cperron          ###   ########.fr       */
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

// return 1 if pipe. else return 0;
int	is_pipe(char *token)
{
	if (token[0] == '|')
		return (1);
	return (0);
}

// return 1 if token is a redir else return 0
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

void	print_cmd_n_arg(t_cmds *cmds)
{
	t_cmds *current;
	int i;
	
	i = 0;
	current = cmds;
	while (current)
	{
		printf(YEL "cmds : %s\n" RESET, current->cmds[i]);
		i++;
		while(cmds->cmds[i])
		{
			printf(" arg :%s\n", current->cmds[i]);
			i++;
		}
		// printf(" arg :%s\n", current->cmds[i]);
		current = current->next;
		i++;
	}
}

int	count_arg(char **tokens, int i)
{
	int n_arg;

	n_arg = 0;
	while (tokens[i] && is_redir(tokens[i]) == 0)
	{
		n_arg++;
		i++;
	}
	printf("nb arg: %d\n", n_arg);
	return (n_arg);
}

int	add_arg(t_cmds *new_node, char **tokens, int i, int n_arg, int c)
{
	while (tokens[i] && n_arg > 1)
	{
		interpret_quotes(NULL, tokens, i);
		new_node->cmds[c] = ft_strdup(tokens[i]);
		printf("arg : %s\n", new_node->cmds[c]);
		c++;
		i++;
		n_arg--;
	}
	new_node->cmds[c] = NULL;
	new_node->next = NULL;
	printf("larg : %s\n", new_node->cmds[c]);
	return (i);
}

int add_cmd(t_cmds **list, char **tokens, int i, int bef_cmd)
{
	t_cmds *new_node;
	int n_arg;
	int c;
	
	c = 0;
	new_node = ft_calloc(1, sizeof(t_cmds));
	n_arg = count_arg(tokens, i);
	new_node->cmds = ft_calloc(sizeof(char*), n_arg + 1);
	new_node->cmds[c] = ft_strdup(tokens[i]);
	printf(YEL "cmds : %s\n" RESET, new_node->cmds[c]);
	c++;
	i++;
	i = add_arg(new_node, tokens, i, n_arg, c);
	addnodecmds(list, new_node);
	// print_cmd_n_arg(*list);
	i = redir_list_3(list, tokens, i, bef_cmd);
	return (i);
}

int	find_cmds(char **tokens, int i)
{
	while (is_redir_2(tokens[i]) == 1)
		i +=2;
	return (i);
}

void	check_cmds(t_cmds **cmds, char **tokens, int num_token)
{
	int i;
	int bef_cmd;

	i = 0;
	bef_cmd = 0;
	while (tokens[i])
	{
		bef_cmd = i;
		i = find_cmds(tokens, i);
		if (tokens[i + 1])
		{
			printf ("THE i: %d\n", i);
			i = add_cmd(cmds, tokens, i, bef_cmd);
	
		}
		i++;
		// printf ("THE i: %d\n", i);
	}
	
}

void	parse_linked_list(t_mini *mini, char **tokens)
{
	t_cmds	*cmds;
	
	cmds = NULL;
	// print_token(tokens);
	check_cmds(&cmds, tokens, 0);
	
	// mini->cmds_list = cmds;
	// cmds = free_linked_list_cmds(&cmds);
	// redir_list(tokens);
	// print_cmds_list(cmds);
}


// void	check_cmds(t_cmds **cmds, char **tokens, int num_token)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (tokens[i])
// 	{
// 		if (is_redir_2(tokens[i]) == 1 && i == 0)
// 		{
// 			find_cmds(tokens, i);
// 			i +=2 ;
// 			i = addnode_end_cmds_first(cmds, tokens, i);
// 			if (is_redir(tokens[i]) == 1)
// 				i++;
// 		}
// 		else
// 		{
// 			while (is_redir(tokens[i]) == 1)
// 			{

// 				i+=2;
// 			}
// 			i = addnode_end_cmds(cmds, tokens, i);
// 			printf("THE i: %d\n", i);
// 			if (!tokens[i])
// 				break;
// 			while (is_redir(tokens[i]) == 1)
// 			{
// 				i+=2;
// 				if (!tokens[i])
// 				break;
// 			}
// 		}
// 		if (!tokens[i])
// 			break;
// 		// i += 2;
// 	}
	
// }

// int 	count_cmds_arg(char **tokens, int i)
// {
// 	int n;

// 	n = 0;
// 	while (tokens[i] && is_redir(tokens[i]) == 0)
// 	{
// 		n++;
// 		i++;
// 	}
// 	printf("nb arg: %d\n", n);
// 	return (n);
// }

// int	addnode_end_cmds(t_cmds **list, char **tokens, int i)
// {
// 	t_cmds *new_node;
// 	int n;
// 	int c;
	
// 	c = 0;
// 	new_node = ft_calloc(1, sizeof(t_cmds));
// 	n = count_cmds_arg(tokens, i);
// 	printf("i: %d\n", i);
// 	printf("n: %d\n", n);
// 	new_node->cmds = ft_calloc(n + 1, sizeof(char*));
// 	if (is_redir(tokens[i]) == 1)
// 	{
// 		// puts("ici");
// 		i++;
// 	}
// 	while (tokens[i] && is_redir(tokens[i]) == 0)
// 	{
// 		interpret_quotes(NULL, tokens, i);
// 		new_node->cmds[c] = ft_strdup(tokens[i]);
// 		if (c == 0)
// 			printf(YEL "cmds : %s\n" RESET, new_node->cmds[c]);
// 		else
// 			printf("arg : %s\n", new_node->cmds[c]);
// 		c++;
// 		i++;
// 	}
// 	new_node->cmds[c] = NULL;
// 	new_node->next = NULL;
// 	printf("arg : %s\n", new_node->cmds[c]);
// 	printf("n: %d\n", n);
// 	redir_list_2(list, tokens, i, n, 1);
// 	addnodecmds(list, new_node);
// 	return (i);
// }

// int 	count_cmds_arg_first(char **tokens, int i)
// {
// 	int n;
// 	int max;

// 	n = 0;
// 	max = i;
// 	// i = 0;
// 	while (is_redir(tokens[i]) == 1)
// 		i += 2;
// 	while (tokens[i] && is_redir(tokens[i]) == 0)
// 	{
// 		n++;
// 		i++;
// 	}
// 	printf("nb arg: %d\n", n);
// 	return (n);
// }

// int	addnode_end_cmds_first(t_cmds **list, char **tokens, int i)
// {
// 	t_cmds *new_node;
// 	int n;
// 	int c;
	
// 	c = 0;
// 	new_node = ft_calloc(1, sizeof(t_cmds));
// 	n = count_cmds_arg_first(tokens, i);
// 	new_node->cmds = ft_calloc(sizeof(char*), n + 1);

	
// 	while (is_redir(tokens[i]) == 1)
// 		i += 2;
// 	interpret_quotes(NULL, tokens, i);
// 	new_node->cmds[c] = ft_strdup(tokens[i]);
// 	printf(YEL "cmds : %s\n" RESET, new_node->cmds[c]);
// 	c++;
// 	i++;
// 	// i = 0;
// 	while (tokens[i] && n > 1)
// 	{
// 		if (is_redir(tokens[i]) == 1)
// 			i++;
// 		interpret_quotes(NULL, tokens, i);
// 		new_node->cmds[c] = ft_strdup(tokens[i]);
// 		printf("arg : %s\n", new_node->cmds[c]);
// 		c++;
// 		i++;
// 		n--;
// 	}
// 	// printf("THE i: %d\n", i);
// 	n--;
// 	new_node->cmds[c] = NULL;
// 	new_node->next = NULL;
// 	printf("larg : %s\n", new_node->cmds[c]);
// 	printf("n: %d\n", n);
// 	redir_list_2(list, tokens, i, n, 0);
// 	addnodecmds(list, new_node);
// 	return (i);
// }