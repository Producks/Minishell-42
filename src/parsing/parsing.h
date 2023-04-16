/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:56:15 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 14:44:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include "../utils/struct.h"
# include "../../libs/readline/history.h"
# include "../../libs/readline/readline.h"
# include "../../libs/Libft/libft.h"
# include "../execution/execution.h"
# include "../cmds/cmds.h"
# include "../lexer/lexer.h"
# include "../interpreter/interpreter.h"

// extern int	g_exit_status;

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define PNK   "\x1B[38;5;206m"
# define RESET "\x1B[0m"

typedef struct s_pos
{
	int		bef_cmd;
	int		pipe;
	int		c;
	int		n_arg;
	int		type;
	t_mini	*mini;
}	t_pos;

//else
int		check_input(t_mini *mini);
int		read_input(t_mini *mini);
int		tokenize(t_mini *mini);

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