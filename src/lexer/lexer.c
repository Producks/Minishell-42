/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:19:53 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/27 20:23:09 by cperron          ###   ########.fr       */
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
	// mini->message = readline(GRN "Minishell > " RESET);
	// < input.txt | wc > output.txt
	// cat < input.txt | > output.txt wc
	mini->message = ft_strdup("  << input.txt < input_two.txt cat | wc >> output.txt > output_two.txt");
	//< rien < chalam << input.txt < input_two.txt cat -s -i -9 | wc -p >> output.txt > output_two.txt >> patitnoir > minishell
	// echo < input.txt cat | wc > output.txt
	// << input.txt < input_two.txt cat | wc >> output.txt > output_two.txt
	// cat1 < input.txt | cat2 | wc | cat3 > test.txt
	literal_tokens = literal_tokenization(mini);
	if (!literal_tokens)
		exit(0); // add later
	dollar_interpreter(mini, literal_tokens);
	// interpret_quotes(mini, literal_tokens, 1); //dangerous check later if fail null = bad
	// for (int i = 0; literal_tokens[i]; i++)
	// 	printf("%s\n", literal_tokens[i]);
	// ft_free(literal_tokens);
	// lol (mini);
	// exit (0);
	parse_linked_list(mini, literal_tokens);
	return ;
}
