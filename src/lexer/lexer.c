/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:19:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/27 20:28:56 by ddemers          ###   ########.fr       */
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

	literal_tokens = literal_tokenization(mini);
	if (!literal_tokens)
		return ;
	if (dollar_interpreter(mini, literal_tokens) == FAILURE)
	{
		ft_free(literal_tokens);
		return ;
	}
	for (int i = 0; literal_tokens[i]; i++)
	{
		interpret_quotes(mini, literal_tokens, i);
		printf("%s\n", literal_tokens[i]);
	}
	ft_free(literal_tokens);
}
