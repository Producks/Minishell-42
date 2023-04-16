/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:20:12 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/15 23:24:41 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../utils/struct.h"
# include "../utils/utils.h"
# include "../errors/error.h"

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

/* Lexer.c */

void	lexer(t_mini *mini);

/* Literal.c */

char	**literal_tokenization(t_mini *mini);

/* Literal_redir.c */

int		isredir(int c);
void	check_if_redir(t_literal *literal, const char *str);

/* Literal_string.c */

void	count_literal_string(t_literal *literal, const char *str);
void	literal_string_sep(t_literal *literal, const char *str);
char	**literal_tokenization(t_mini *mini);

/* Literal_error.c */

void	check_bracket_error(t_literal *literal, const char *str);
void	check_pipe_error(t_literal *literal);
void	check_double_redir_error(t_literal *literal);
void	check_single_redir_error(t_literal *literal);
void	literal_error_handling(t_literal *literal,
			const char *str, int err_nbr);

/* Check_expandable.c */

bool	check_expandable(char c);

/* literal_sigpipe_check.c */

int		literal_sigpipe_check(t_literal *literal);

#endif