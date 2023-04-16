/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:32:33 by cperron           #+#    #+#             */
/*   Updated: 2023/04/10 22:16:14 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_cmds(char **tokens, int i)
{
	while (is_redir_2(tokens[i]) == 1 && tokens[i + 2])
		i += 2;
	return (i);
}

int	find_pipe(char **tokens, int i)
{	
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) == 1)
			return (i);
		i++;
	}
	return (0);
}

void	check_arg(char **tokens, int i, t_pos *pos)
{
	if (pos->pipe != 0)
		pos->n_arg = count_arg_2(tokens, i, pos->pipe);
	else
		pos->n_arg = count_arg(tokens, i);
}

int	go_to_cmd(char **tokens, int i, t_pos *pos)
{
	while (i < pos->pipe && pos->pipe != 0)
	{
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		else
			break ;
	}
	return (i);
}

int	check_redir(t_redir **redir, char **tokens, int i, t_pos *pos)
{
	if (ft_strcmp(tokens[i], "<") == 0)
	{
		pos->type = 52;
		if (addnode_end_redir(redir, 0, tokens[i + 1], pos) == FAILURE)
			return (FAILURE);
	}
	if (ft_strcmp(tokens[i], ">>") == 0)
	{
		pos->type = 53;
		if (addnode_end_redir(redir, 1, tokens[i + 1], pos) == FAILURE)
			return (FAILURE);
	}
	if (ft_strcmp(tokens[i], "<<") == 0)
	{
		pos->type = 54;
		if (addnode_end_redir(redir, 0, tokens[i + 1], pos) == FAILURE)
			return (FAILURE);
	}
	return (i);
}
