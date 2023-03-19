/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:19:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 00:20:57 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/struct.h"
#include "../parsing/parsing.h"
#include "lexer.h"
#include <stdio.h>

/*Store an array of tokens from the user command in the mini struct.*/
void	lexer(t_mini *mini)
{
	char	**literal_tokens;
	char	**interpreted_tokens;
	
	free (mini->message);
	mini->message = readline(GRN "Minishell > " RESET);
	literal_tokens = literal_tokenization(mini);
	if (!literal_tokens)
		exit(0);
	for (int i = 0; literal_tokens[i]; i++)
		printf("%s\n", literal_tokens[i]);
	exit (0);
	//interpreted_tokens = interpreted_tokenization(mini, literal_tokens);
	return ;
}
