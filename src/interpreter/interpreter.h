/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:11:07 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 00:10:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

# include "../../libs/Libft/libft.h"
# include "../utils/struct.h"
# include "../utils/utils.h"
# include "../errors/error.h"
# include <stdbool.h>
# include <stdio.h>

# define SUCCESS 0
# define FAILURE -1
# define SINGLE_QUOTE 39 
# define DOUBLE_QUOTE 34
# define DOLLAR_SIGN  36
# define QUESTION_MARK 63
# define UNDERSCORE 95

typedef struct s_expandable
{
	size_t	length;
	int		dollar_index_start;
	int		index;
	int		ret;
	char	*env_str;
	char	*env_check;
	char	*original_cut;
	char	*str_literal;
	char	*cut_result;
}	t_expandable;

typedef struct s_dollar
{
	char	*result;
	int		index;
	int		ret;
}	t_dollar;

/*Interpreter.c*/

char	*interpreter(char *str, t_mini *mini);

/*dollar.interpreter.c*/

char	*dollar_interpreter(char *str, t_mini *mini);

/*quotes_interpreter.c*/

char	*interpret_quotes(char *str);

/*dollar_expandable.c*/

int		dollar_expandable(t_dollar *dollar, t_mini *mini);

/*Interpreter_utils.c*/

bool	check_expandable(char c);

char	**cut_into_pieces(char *str);

/* Dollar_length_handle.c */

int		dollar_length_h(t_dollar *dollar, t_mini *mini, int start);

#endif