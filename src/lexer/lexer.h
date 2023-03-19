/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:20:12 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 01:13:58 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../libs/Libft/libft.h"
# include "../main/struct.h"
# include <stdbool.h>

# define FAILURE -1
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

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

#endif