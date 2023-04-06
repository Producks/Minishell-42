/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redir_christo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:45:03 by cperron           #+#    #+#             */
/*   Updated: 2023/04/05 19:40:54 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	addnode_end_redir(t_redir **list, int type, int dir, char *filename)
{
	t_redir *new_node;
	
	new_node = ft_calloc(1, sizeof(t_redir));
	new_node->type = type;
	if (dir == 1)
		new_node->out = true;
	if (dir == 0)
		new_node->in = true;
	if (filename)
		new_node->filename = interpret_quotes(filename);
	// puts(new_node->filename);
	addnoderedir(list, new_node);
}

int	check_pipe_in(t_redir **redir, char **tokens, int i, int n)
{
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			addnode_end_redir(redir, 50, 1, NULL);
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
	return (i);
}

int	redir_list_3(t_cmds *new_node, char **tokens, int i, t_pos *pos)
{
	t_redir *redir;
	
	redir = NULL;
	i = pos->bef_cmd;
	check_pipe_in(&redir, tokens, i, 0);
	check_pipe_out(&redir, tokens, i);
	i = check_redir_2(&redir, tokens, i, pos->bef_cmd);
	new_node->redir_list = redir;
	return (i);
}
