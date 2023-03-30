/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_christo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:59:33 by cperron           #+#    #+#             */
/*   Updated: 2023/03/30 00:49:58 by ddemers          ###   ########.fr       */
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

void	*free_linked_list_cmds(t_cmds **head)
{
	t_cmds *current;
	t_cmds *previous;
	
	current = *head;
	while (current)
	{
		previous = current;
		current = current->next;
		printf("cmds add : %p\n", previous->cmds);
		free(previous->cmds);
		printf("cmds add : %p\n", previous->cmds);
		free_linked_list_redirr(&previous->redir_list);
		free(previous);
		printf("cmds add : %p\n", previous->cmds);
		previous = NULL;
		// printf("cmds add : %p\n", previous->cmds);
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
		printf("add : %p\n", current);
		printf("in :%d\n", current->in);
		printf("out :%d\n", current->out);
		printf("filename : %s\n\n", current->filename);
		printf("next : %p\n", current->next);
		current = current->next;
		i++;
	}

}


void	printall(t_cmds *cmds)
{
	t_cmds *current;
	int i;
	
	i = 0;
	current = cmds;
	while (current)
	{
		i = 0;
		printf(YEL "cmds : %s\n" RESET, current->cmds[i]);
		i++;
		while(current->cmds[i])
		{
			printf(" arg :%s\n", current->cmds[i]);
			i++;
		}
		printf(" larg : %s\n", current->cmds[i]);
		printf(" redir : %p\n", current->redir_list);
		print_redir_list(current->redir_list);
		current = current->next;
		// puts("ici");
		i++;
	}
}

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

int	count_arg(char **tokens, int i)
{
	int n_arg;

	n_arg = 0;
	// printf("nb arg: %d\n", n_arg);
	// printf("i: %d\n", i);
	while (tokens[i] && is_pipe(tokens[i]) == 0)
	{
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		else
		{
			n_arg++;
			i++;
		} 
	
	}
	// printf("nb arg: %d\n", n_arg);
	return (n_arg);
}

int	count_arg_2(char **tokens, int i, int pipe_p)
{
	int n_arg;

	n_arg = 0;
	while (tokens[i] && i < pipe_p)
	{
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		else
			n_arg++;
		i++;
	}
	
	return (n_arg);
}

int	add_arg(t_cmds *new_node, char **tokens, int i, int n_arg, int c)
{
	while (tokens[i] && n_arg > 1)
	{
		interpret_quotes(NULL, tokens, i);
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		new_node->cmds[c] = ft_strdup(tokens[i]);
		// printf("arg : %s\n", new_node->cmds[c]);
		c++;
		i++;
		n_arg--;
	}
	
	new_node->cmds[c] = NULL;
	new_node->next = NULL;
	// printf("larg : %s\n", new_node->cmds[c]);
	return (i);
}

int	count_cmds(char **tokens)
{
	int i;
	int n_cmds;

	i = 0;
	n_cmds = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) == 1)
			n_cmds++;
		i++;
	}
	return (n_cmds + 1);
}


int add_cmd_2(t_cmds **list, char **tokens, int i, int bef_cmd, int pipe_p) // problem here won't pass norm
{
	t_cmds *new_node;
	int n_arg;
	int c;
	
	c = 0;
	new_node = ft_calloc(1, sizeof(t_cmds));
	// new_node->nb_cmds = count_cmds(tokens);
	// printf("n_cmds ; %d\n", new_node->nb_cmds);
	if (pipe_p != 0)
		n_arg = count_arg_2(tokens, i, pipe_p);
	else 
		n_arg = count_arg(tokens, i);
	// printf ("n arg: %d\n", n_arg);
	// puts("ici");
	//new_node->cmds = ft_calloc(sizeof(char*), n_arg + 1);
	new_node->cmds = ft_calloc(sizeof(char*), n_arg + 1);
	while (i < pipe_p && pipe_p != 0)
	{
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		else
			break;
	}
	// printf ("THE i: %d\n", i);
	if (is_pipe(tokens[i]) == 1)
		new_node->cmds[c] = NULL;
	else
		new_node->cmds[c] = ft_strdup(tokens[i]);
	//new_node->redir_list = ft_calloc(1, sizeof(t_redir)); // leak here, if commented goes away. What is this for exactly?
	// printf(YEL "cmds : %s\n" RESET, new_node->cmds[c]);
	c++;
	i++;
	i = add_arg(new_node, tokens, i, n_arg, c);
	i = redir_list_3(new_node, tokens, i, bef_cmd);
	addnodecmds(list, new_node);
	// puts("ici");
	// printf ("THE i: %d\n", i);
	return (i);
}

int	find_cmds(char **tokens, int i)
{
	while (is_redir_2(tokens[i]) == 1)
		i +=2;
	return (i);
}

int	find_pipe(char **tokens, int i)
{	
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) == 1)
			return(i);
		i++;
	}
	return (0);
}

void    check_cmds(t_cmds **cmds, char **tokens, int num_token)
{
	int i;
	int bef_cmd;
	int	pipe_p;
	int n;

	n = 0;
	i = 0;

	bef_cmd = 0;
	n = count_cmds(tokens);
	//printf("n_cmds ; %d\n", n);
	while (tokens[i])
	{
		pipe_p = 0;
		bef_cmd = i;
		pipe_p = find_pipe(tokens, i);
		
		// printf ("pipe_p: %d\n", pipe_p);
		// printf ("THE i: %d\n", i);
		if (pipe_p == 0)
			i = find_cmds(tokens, i);
		i = add_cmd_2(cmds, tokens, i, bef_cmd, pipe_p);
		//printf ("THE i: %d\n", i);
		if (pipe_p != 0)
			i++;
		// i++;
		// i++;
		
	}
	
}

void	parse_linked_list(t_mini *mini, char **tokens)
{
	t_cmds	*cmds;
	
	cmds = NULL;
	
	// cmds = ft_calloc(1, sizeof(t_cmds));
	// cmds->nb_cmds = count_cmds(tokens);
	// printf("n_cmds ; %d\n", cmds->nb_cmds);
	
	// print_token(tokens);
	// puts ("ici");
	
	
	check_cmds(&cmds, tokens, 0);
	mini->cmds_list = cmds;
	//printall(cmds);
	//tokens = ft_free(tokens);
	execution(mini);
	//cmds = free_linked_list_cmds(&cmds);
	// printall(cmds);
}
