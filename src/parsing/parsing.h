/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:56:15 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 14:09:45 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include "../execution/execution.h"
# include "../interpreter/interpreter.h"


typedef struct s_pos
{
	int		bef_cmd;
	int		pipe;
	int		c;
	int		n_arg;
	int		type;
	t_mini	*mini;
}	t_pos;

//list_redir
int		redir_list_3(t_cmds *new_node, char **tokens, int i, t_pos *pos);
int		addnode_end_redir(t_redir **list, int dir, char *filename, t_pos *pos);

//cmds_list
void	parse_linked_list(t_mini *mini, char **tokens);

//list_utils
void	addnodecmds(t_cmds **list, t_cmds *new_node);
void	addnoderedir(t_redir **list, t_redir *new_node);

//test_list
void	print_redir_list(t_redir *redir);
void	print_token(char **tokens);
void	printall(t_cmds *cmds);

//parsing_utils_1
int		is_pipe(char *token);
int		is_redir_2(char *token);
int		is_redir(char *token);
int		count_arg(char **tokens, int i);
int		count_arg_2(char **tokens, int i, int pipe_p);

//parsing_utils_2
int		find_cmds(char **tokens, int i);
int		find_pipe(char **tokens, int i);
void	check_arg(char **tokens, int i, t_pos *pos);
int		go_to_cmd(char **tokens, int i, t_pos *pos);
int		check_redir(t_redir **redir, char **tokens, int i, t_pos *pos);

#endif