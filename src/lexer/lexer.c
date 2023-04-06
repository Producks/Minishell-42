/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:19:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/05 21:42:55 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/struct.h"
#include "../parsing/parsing.h"
#include "lexer.h"
#include "../interpreter/interpreter.h"

/*Store an array of tokens from the user command in the mini struct.*/
void	lexer(t_mini *mini)
{
	char	**literal_tokens;
	int		ret;

	literal_tokens = literal_tokenization(mini);
	if (!literal_tokens)
		return ;
	// if (dollar_interpreter(mini, literal_tokens) == FAILURE)
	// {
	// 	ft_free(literal_tokens);
	// 	return ;
	// }
	parse_linked_list(mini, literal_tokens);
	free_linked_list_mini(&mini->cmds_list); // add cleanup later
}
