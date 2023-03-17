/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:20:12 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/17 08:30:26 by ddemers          ###   ########.fr       */
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
	int		count;
	int		ret;
	char	flag;
	char	type;
	char	**array;
}	t_literal;

void	redirection_check(t_literal *literal, const char *str);

/*literal.c*/

char	**literal_tokenization(t_mini *mini);

#endif