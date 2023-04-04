/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:06:19 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/04 12:05:22 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

bool	check_expandable(char c)
{
	if ((ft_isalpha(c) || ft_isdigit(c) || c == UNDERSCORE))
		return (true);
	return (false);
}

// void	single_quote_inc(t_expandable *expand)
// {
// 	expand->index++;
// 	while (expand->str_literal[expand->index] != SINGLE_QUOTE)
// 		expand->index++;
// 	expand->index++;
// }
