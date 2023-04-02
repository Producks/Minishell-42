/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_christo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:59:33 by cperron           #+#    #+#             */
/*   Updated: 2023/04/01 19:41:50 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	add_arg(t_cmds *new_node, char **tokens, int i, int n_arg, int c)
{
		while (tokens[i] && n_arg > 1)
		{
			if (is_redir_2(tokens[i]) == 1)
				i += 2;
			new_node->cmds[c] = interpret_quotes(tokens[i]);
			c++;
			i++;
			n_arg--;
		}

	new_node->cmds[c] = NULL;
	new_node->next = NULL;
	return (i);
}

int add_the_cmd(t_cmds *new_node, char **tokens, int i, int c)
{
	if (is_pipe(tokens[i]) == 1)
		new_node->cmds[c] = NULL;
	else if (is_redir_2(tokens[i]) == 1)
		new_node->cmds[c] = NULL;
	else
		new_node->cmds[c] = interpret_quotes(tokens[i]);
	return (i + 1);
}


int create_cmd_node(t_cmds **list, char **tokens, int i, t_pos *pos)
{
	t_cmds *new_node;
	int n_arg;
	int c;
	
	c = 0;
	new_node = ft_calloc(1, sizeof(t_cmds));
	if (pos->pipe != 0)
		n_arg = count_arg_2(tokens, i, pos->pipe);
	else 
		n_arg = count_arg(tokens, i);
	new_node->cmds = ft_calloc(sizeof(char*), n_arg + 2);
	while (i < pos->pipe && pos->pipe != 0)
	{
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		else
			break;
	}
	i = add_the_cmd(new_node, tokens, i, c);
	c++;
	i = add_arg(new_node, tokens, i, n_arg, c);
	i = redir_list_3(new_node, tokens, i, pos);
	addnodecmds(list, new_node);
	return (i);
}

void    check_cmds(t_cmds **cmds, char **tokens, int num_token)
{
	int i;
	int bef_cmd;
	int	pipe_p;
	t_pos	pos;

	i = 0;
	pos.bef_cmd = 0;
	while (tokens[i])
	{
		pos.pipe = 0;
		pos.bef_cmd = i;
		pos.pipe = find_pipe(tokens, i);
		if (pos.pipe == 0)
			i = find_cmds(tokens, i);
		i = create_cmd_node(cmds, tokens, i, &pos);
		if (pos.pipe != 0)
			i++;
	}
}

void	parse_linked_list(t_mini *mini, char **tokens)
{
	t_cmds	*cmds;
	
	cmds = NULL;
	check_cmds(&cmds, tokens, 0);
	mini->cmds_list = cmds;
	printall(cmds);
	ft_free(tokens);
	execution(mini);
}

// int add_cmd(t_cmds **list, char **tokens, int i, t_pos *pos)
// {
// 	t_cmds *new_node;
// 	int n_arg;
// 	int c;
	
// 	c = 0;
// 	new_node = ft_calloc(1, sizeof(t_cmds));

// 	if (pos->pipe != 0)
// 		n_arg = count_arg_2(tokens, i, pos->pipe);
// 	else 
// 		n_arg = count_arg(tokens, i);
// 	new_node->cmds = ft_calloc(sizeof(char*), n_arg + 2);
// 	while (i < pos->pipe && pos->pipe != 0)
// 	{
// 		if (is_redir_2(tokens[i]) == 1)
// 			i += 2;
// 		else
// 			break;
// 	}
	
// 	if (is_pipe(tokens[i]) == 1)
// 		new_node->cmds[c] = NULL;
// 	else if (is_redir_2(tokens[i]) == 1)
// 		new_node->cmds[c] = NULL;
// 	else
// 		new_node->cmds[c] = interpret_quotes(tokens[i]);

		
// 	c++;
// 	i++;
	
// 	i = add_arg(new_node, tokens, i, n_arg, c);
	
// 	i = redir_list_3(new_node, tokens, i, pos);

// 	addnodecmds(list, new_node);
// 	return (i);
// }
