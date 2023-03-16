/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:20:12 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/15 20:03:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../libs/Libft/libft.h"
# include "../main/struct.h"
# include <stdbool.h>

bool	redirection_check(const char *str);

/*literal.c*/

char	**literal_tokenization(t_mini *mini);

#endif