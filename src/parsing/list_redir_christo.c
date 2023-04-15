/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redir_christo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:45:03 by cperron           #+#    #+#             */
/*   Updated: 2023/04/15 12:23:55 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	addnode_end_redir(t_redir **list, int dir, char *filename, t_pos *pos)
{
	t_redir	*new_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
		return (print_errno(ENOMEM), FAILURE);
	new_node->type = pos->type;
	if (dir == 1)
		new_node->out = true;
	if (dir == 0)
		new_node->in = true;
	if (filename)
	{
		// if (pos->type == 54)
		// 	new_node->filename = interpret_quotes(filename);
		// else
		new_node->filename = interpreter(filename, pos->mini);
		if (!new_node->filename)
			return (FAILURE);
	}
	addnoderedir(list, new_node);
	return (SUCCESS);
}

int	check_pipe_in(t_redir **redir, char **tokens, int i, t_pos *pos)
{
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			pos->type = 50;
			if (addnode_end_redir(redir, 1, NULL, pos) == FAILURE)
				return (FAILURE);
			return (1);
		}	
		i++;
	}
	return (0);
}

int	check_pipe_out(t_redir **redir, char **tokens, int i, t_pos *pos)
{
	int	j;

	j = 0;
	while (tokens[j] && j < i)
	{
		if (ft_strcmp(tokens[j], "|") == 0)
		{
			pos->type = 50;
			if (addnode_end_redir(redir, 0, NULL, pos) == FAILURE)
				return (FAILURE);
			return (1);
		}	
		j++;
	}
	return (0);
}

int	check_redir_2(t_redir **redir, char **tokens, int i, t_pos *pos)
{
	int	max;

	max = i;
	i = pos->bef_cmd;
	while (tokens[i] && is_pipe(tokens[i]) == 0)
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			pos->type = 51;
			if (addnode_end_redir(redir, 1, tokens[i + 1], pos) == FAILURE)
				return (FAILURE);
		}
		i = check_redir(redir, tokens, i, pos);
		i++;
	}
	return (i);
}

int	redir_list_3(t_cmds *new_node, char **tokens, int i, t_pos *pos)
{
	t_redir	*redir;

	redir = NULL;
	i = pos->bef_cmd;
	if (check_pipe_in(&redir, tokens, i, pos) == FAILURE)
		return (FAILURE);
	if (check_pipe_out(&redir, tokens, i, pos) == FAILURE)
		return (FAILURE);
	i = check_redir_2(&redir, tokens, i, pos);
	if (i == FAILURE)
		return (FAILURE);
	new_node->redir_list = redir;
	return (i);
}
