/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:20:12 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/22 13:57:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../libs/Libft/libft.h"
# include "../main/struct.h"
# include "../utils/utils.h"
# include <stdbool.h>
# include <stdio.h>

# define SUCCESS 0
# define FAILURE -1
# define SINGLE_QUOTE 39 
# define DOUBLE_QUOTE 34
# define DOLLAR_SIGN  36
# define QUESTION_MARK 63
# define UNDERSCORE 95

extern int	g_exit_status;

typedef struct s_literal
{
	int		index;
	int		i;
	int		count;
	int		ret;
	char	flag;
	char	type;
	char	*str;
	char	**array;
}	t_literal;

/*Lexer.c*/
void	lexer(t_mini *mini);

/*Literal.c*/
char	**literal_tokenization(t_mini *mini);
/*Literal_redir.c*/
int		isredir(int c);
void	check_if_redir(t_literal *literal, const char *str);
/*Literal_string.c*/
void	count_literal_string(t_literal *literal, const char *str);
void	literal_string_sep(t_literal *literal, const char *str);
char	**literal_tokenization(t_mini *mini);
/*Literal_error.c*/
void	literal_error_handling(t_literal *literal, const char *str, int err_nbr);
void	literal_check_errors(t_literal *literal);

/*tokens_interpreter.c*/
//int		tokens_interpreter(t_mini *mini, char **literal);
/*dollar.interpreter.c*/
int		dollar_interpreter(t_mini *mini, char **literal);
/*quotes_interpreter.c*/
int		interpret_quotes(t_mini *mini, char **tokens, int index);
/*dollar_expandable.c*/
int		dollar_expandable(t_mini *mini, char **literal, int index);

#endif