/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:56:15 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 14:00:38 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stdio.h>
#include <string.h>
//#include <readline/readline.h> // fix later
//#include <readline/history.h> // fix later
# include "../main/struct.h"
# include "../../libs/readline/history.h"
# include "../../libs/readline/readline.h"
# include "../../libs/Libft/libft.h"
# include "../execution/execution.h"
# include "../cmds/cmds.h"
# include "../lexer/lexer.h"

extern int	g_exit_status;

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct s_pos
{
    int				bef_cmd;
	int				pipe;
	int				c;
	t_mini			*mini;
}	t_pos;

int check_input(t_mini *mini);
int	read_input(t_mini *mini);
int tokenize(t_mini *mini);

void	redir_list(char **tokens);
void	redir_list_2(t_cmds **cmds, char **tokens, int i, int n, int f);
int		redir_list_3(t_cmds *new_node, char **tokens, int i, t_pos *pos);
int		is_pipe(char *token);
int 	is_redir(char *token);
void	*free_linked_list_redirr(t_redir **head);
void	parse_linked_list(t_mini *mini, char **tokens);
//int		interpret_quotes(t_mini *mini, char **tokens, int index);

void 	addnodecmds(t_cmds **list, t_cmds *new_node);
void 	addnoderedir(t_redir **list, t_redir *new_node);

//test_list
void	print_redir_list(t_redir *redir);
void	print_token(char **tokens);
void	printall(t_cmds *cmds);

//parsing_utils_1
int		is_pipe(char *token);
int 	is_redir_2(char *token);
int 	is_redir(char *token);
int		count_arg(char **tokens, int i);
int		count_arg_2(char **tokens, int i, int pipe_p);

//parsing_utils_2
int		add_arg(t_cmds *new_node, char **tokens, int i, int n_arg, int c);
int		find_cmds(char **tokens, int i);
int		find_pipe(char **tokens, int i);

#endif