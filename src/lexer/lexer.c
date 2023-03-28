/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:19:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/27 23:39:48 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../main/struct.h"
#include "../parsing/parsing.h"
#include "lexer.h"

/*Store an array of tokens from the user command in the mini struct.*/
void	lexer(t_mini *mini)
{
	char	**literal_tokens;
	int		ret;


	// mini->message = ft_strdup("");
	literal_tokens = literal_tokenization(mini);
	if (!literal_tokens)
		return ;
	if (dollar_interpreter(mini, literal_tokens) == FAILURE)
	{
		ft_free(literal_tokens);
		return ;
	}
	parse_linked_list(mini, literal_tokens);
	ft_free(literal_tokens);
}
 // echo hello > cat