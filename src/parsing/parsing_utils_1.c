/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:22:52 by cperron           #+#    #+#             */
/*   Updated: 2023/04/03 19:10:44 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// return 1 if pipe. else return 0;
int	is_pipe(char *token)
{
	if (token[0] == '|')
		return (1);
	return (0);
}

// return 1 if token is a redir else return 0
int is_redir_2(char *token)
{
	if (token[0] == '<' || token[0] == '>')
		return (1);
	return (0);
}

// return 1 if token is a redir else return 0
int is_redir(char *token)
{
	if (token[0] == '<' || token[0] == '>' || token[0] == '|')
		return (1);
	return (0);
}

int	count_arg(char **tokens, int i)
{
	int n_arg;

	n_arg = 0;
	while (tokens[i] && is_pipe(tokens[i]) == 0)
	{
		if (is_redir_2(tokens[i]) == 1)
			i += 2;
		else
		{
			n_arg++;
			i++;
		} 
	
	}
	return (n_arg);
}

int	count_arg_2(char **tokens, int i, int pipe_p)
{
	int n_arg;

	n_arg = 0;
	while (tokens[i] && i < pipe_p)
	{
		if (is_redir_2(tokens[i]) == 1)	
			i += 2;
		else
		{
			n_arg++;
			i++;
		}
	}
	// printf("nb arg: %d\n", n_arg);
	return (n_arg);
}
