/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:02:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/17 09:57:40 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	check_redir_count(t_literal *literal, const char *str)
{
	literal->type = str[literal->index];
	if (literal->type == str[literal->index + 1]) // check if double redir
		literal->index += 2;
	else
		literal->index++;
	if (str[literal->index] != ' ') // mean something is glued +2
	{
		while (str[literal->index] && str[literal->index] != ' ')
			literal->index++;
		literal->count += 2;
		return ;
	}
	while (str[literal->index] && str[literal->index] == ' ') // not glued +1
		literal->index++;
	literal->count += 1;
}

void	literal_count(t_literal *literal, const char *str)
{
	redirection_check(literal, str + literal->index); // check for redirection syntax error
	if (literal->ret == FAILURE)
		return ;
	if (literal->ret == true)
		return (check_redir_count(literal, str)); // check if redir is glued to something
	if (str[literal->index] == SINGLE_QUOTE || str[literal->index] == DOUBLE_QUOTE) // check if character is a quote, if so check if there no /0
	{
		literal->flag = str[literal->index];
		literal->index++;
		while (str[literal->index] != literal->flag && str[literal->index])
			literal->index++;
		if (!str[literal->index])
		{
			printf("ERROR\n");
			literal->count = -1;
			return ;
		}
		literal->index++;
		literal->count += 1;
		while (str[literal->index] == ' ')
			literal->index++;
		return ;	
	}
	while (str[literal->index] && str[literal->index] != ' ')
		literal->index++;
	literal->count += 1;
	while (str[literal->index] == ' ')
		literal->index++;
}


void	count_tokens_literal(t_literal *literal, const char *str)
{
	while (str[literal->index] == ' ' && str[literal->index])
		literal->index++;
	while (str[literal->index])
	{
		literal_count(literal, str);
		if (literal->ret == -1)
			break ;
	}
}

void	init_literal_struct(t_literal *literal)
{
	literal->index = 0;
	literal->count = 0;
	literal->ret = 0;
	literal->flag = 0;
	literal->type = 0;
	literal->array = NULL;
}

char	**literal_tokenization(t_mini *mini)
{
	t_literal	literal;
	
	if (!mini->cmd)
		return (NULL);
	//mini->message = ft_strdup("t >test");
	init_literal_struct(&literal);
	count_tokens_literal(&literal, "t '");
	printf("Count: %d\n", literal.count);
	exit (0);
	if (literal.count == -1)
		return (NULL);
	return (literal.array);
}
