/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:19:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/20 14:28:04 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/struct.h"
#include "../parsing/parsing.h"
#include "lexer.h"

void	lol(t_mini *mini)
{
	mini->env_copy = ft_free(mini->env_copy);
	mini->cmd = ft_free(mini->cmd);
	if (mini->message)
		free (mini->message);
	close(mini->fd_in);
	close(mini->fd_out);
}

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
	// for (int i = 0; literal_tokens[i]; i++)
	// 	printf("%s\n", literal_tokens[i]);
	dollar_interpreter(mini, literal_tokens);
	interpret_quotes(mini, literal_tokens, 1); //dangerous check later if fail null = bad
	//tokens_interpreter(mini, literal_tokens);
	for (int i = 0; literal_tokens[i]; i++)
		printf("%s\n", literal_tokens[i]);
	ft_free(literal_tokens);
	lol (mini);
	exit (0);
	return ;
}
