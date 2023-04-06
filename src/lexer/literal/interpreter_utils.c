/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:06:19 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 14:11:38 by cperron          ###   ########.fr       */
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
