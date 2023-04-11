/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_christo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:59:33 by cperron           #+#    #+#             */
/*   Updated: 2023/04/10 22:57:02 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../interpreter/interpreter.h"

int	add_arg(t_cmds *new_node, char **tokens, int i, t_pos *pos)
{
	while (tokens[i] && pos->n_arg > 1)
	{
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		if (tokens[i])
		{
			new_node->cmds[pos->c] = interpreter(tokens[i], pos->mini);
			if (!new_node->cmds[pos->c])
				return (FAILURE);
		}
		pos->c++;
		i++;
		pos->n_arg--;
	}
	new_node->next = NULL;
	return (i);
}

int	add_the_cmd(t_cmds *new_node, char **tokens, int i, t_pos *pos)
{
	if (is_pipe(tokens[i]) == 1)
		new_node->cmds[pos->c] = NULL;
	else if (is_redir_2(tokens[i]) == 1)
		new_node->cmds[pos->c] = NULL;
	else
	{
		new_node->cmds[pos->c] = interpreter(tokens[i], pos->mini);
		if (!new_node->cmds[pos->c])
			return (FAILURE);
	}
	return (i + 1);
}

int	create_cmd_node(t_cmds **list, char **tokens, int i, t_pos *pos)
{
	t_cmds	*new_node;

	pos->c = 0;
	new_node = ft_calloc(1, sizeof(t_cmds));
	if (!new_node)
		return (print_errno(ENOMEM), FAILURE);
	check_arg(tokens, i, pos);
	new_node->cmds = ft_calloc(sizeof(char *), pos->n_arg + 2);
	if (!new_node->cmds)
		return (free(new_node), print_errno(ENOMEM), FAILURE);
	i = add_the_cmd(new_node, tokens, i, pos);
	if (i == FAILURE)
		return (free_linked_list_mini(&new_node), FAILURE);
	pos->c++;
	i = add_arg(new_node, tokens, i, pos);
	if (i == FAILURE)
		return (free_linked_list_mini(&new_node), FAILURE);
	i = redir_list_3(new_node, tokens, i, pos);
	if (i == FAILURE)
		return (free_linked_list_mini(&new_node), FAILURE);
	addnodecmds(list, new_node);
	return (i);
}

int	check_cmds(t_cmds **cmds, char **tokens, t_mini *mini)
{
	int		i;
	int		bef_cmd;
	int		pipe_p;
	t_pos	pos;

	i = 0;
	pos.mini = mini;
	pos.bef_cmd = 0;
	while (tokens[i])
	{
		pos.pipe = 0;
		pos.bef_cmd = i;
		pos.pipe = find_pipe(tokens, i);
		if (pos.pipe == 0)
			i = find_cmds(tokens, i);
		i = create_cmd_node(cmds, tokens, i, &pos);
		if (i == FAILURE)
			return (FAILURE);
		if (pos.pipe != 0)
			i++;
	}
	return (SUCCESS);
}

void	parse_linked_list(t_mini *mini, char **tokens)
{
	t_cmds	*cmds;

	cmds = NULL;
	if (check_cmds(&cmds, tokens, mini) == FAILURE)
	{
		free_double_array(tokens);
		return ;
	}
	mini->cmds_list = cmds;
	free_double_array(tokens);
	execution(mini);
}
// printall(cmds);

// i = go_to_cmd(tokens, i, pos); bef add_the_cmd in create cmd_node

//make re; make run
//echo -nnnnnnnnnnnn hello
//echo $A lol
// echo "" lol
// echo $USER