/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:02:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 00:07:44 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

extern int	g_exit_status;

void	literal_error_handling(t_literal *literal, const char *str, int error_nbr)
{
	write(2, str, ft_strlen(str));
	g_exit_status = error_nbr;
	literal->ret = -1;
}

int	isredir(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	double_redir_check(t_literal *literal, const char *str)
{
	literal->str[literal->i++] = 29;
	literal->str[literal->i++] = str[literal->index++];
	literal->str[literal->i++] = str[literal->index++];
	literal->str[literal->i++] = 29;
}

void	single_redir_check(t_literal *literal, const char *str)
{
	literal->str[literal->i++] = 29;
	literal->str[literal->i++] = str[literal->index++];
	literal->str[literal->i++] = 29;
}

void	pipe_redir_check(t_literal *literal, const char *str)
{
	while (ft_isspace(str[literal->index]))
		literal->index++;
	return ;
}


void	check_if_redir(t_literal *literal, const char *str)
{
	if (isredir(str[literal->index]))
	{
		literal->type = str[literal->index];
		if (isredir(str[literal->index + 1]))
			double_redir_check(literal, str);
		else
			single_redir_check(literal, str);
	}
	else
		literal->str[literal->i++] = str[literal->index++];
}

void	check_quotes_literal(t_literal *literal, const char *str)
{
	literal->type = str[literal->index];
	literal->str[literal->i++] = str[literal->index++];
	while (str[literal->index] != literal->type && str[literal->index])
		literal->str[literal->i++] = str[literal->index++];
	if (!str[literal->index])
		return (literal_error_handling(literal, "minishell: incorrect input\n", 2));
	literal->str[literal->i++] = str[literal->index++];
}

void	literal_string_sep(t_literal *literal, const char *str)
{
	literal->index = 0;
	while (str[literal->index])
	{
		if (ft_isspace(str[literal->index]))
		{
			literal->str[literal->i++] = 29;
			while (ft_isspace(str[literal->index]))
				literal->index++;
		}
		while (!ft_isspace(str[literal->index]) && str[literal->index])
		{
			if (str[literal->index] == SINGLE_QUOTE || str[literal->index] == DOUBLE_QUOTE) // check if quotes
				check_quotes_literal(literal, str);
			else
				check_if_redir(literal, str); // check if redir
			if (literal->ret == -1)
				return ;
		}
	}
	literal->str[literal->i] = '\0';
}

void	count_literal_string(t_literal *literal, const char *str)
{
	while (str[literal->index])
	{
		if (isredir(str[literal->index]))
		{
			literal->index++;
			literal->count += 3;
		}
		else
		{
			literal->index++;
			literal->count++;
		}
	}
	literal->count++;
}

void	init_literal_struct(t_literal *literal)
{
	literal->index = 0;
	literal->i = 0;
	literal->count = 0;
	literal->ret = 0;
	literal->flag = 0;
	literal->type = 0;
	literal->array = NULL;
}

void	check_single_redir_error(t_literal *literal)
{
	if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
		return (literal_error_handling(literal, "Pipe right token\n", 2));
	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
		return (literal_error_handling(literal, "Pipe right empty\n", 2));
	if (literal->index == 0) // check if pipe has no args to the left
		return (literal_error_handling(literal, "Pipe left empty\n", 2));
	if (isredir(literal->array[literal->index - 1][0]))
		return (literal_error_handling(literal, "Argument to left of pipe\n", 2));
}

void	check_double_redir_error(t_literal *literal)
{
	// if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
	// 	return (literal_error_handling(literal, "ERRORdd\n", 2));
	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
		return (literal_error_handling(literal, "Pipe right empty\n", 2));
	if (literal->index == 0) // check if pipe has no args to the left
		return (literal_error_handling(literal, "da\n", 2));
	if (isredir(literal->array[literal->index - 1][0]))
		return (literal_error_handling(literal, "ta\n", 2));
	return ;
}

void	check_pipe_error(t_literal *literal)
{
	if (isredir(literal->array[literal->index][1])) // check if there another redirection glued to it
		return (literal_error_handling(literal, "Pipe right token\n", 2));
	if (!literal->array[literal->index + 1]) // check if pipe has no args to the right
		return (literal_error_handling(literal, "Pipe right empty\n", 2));
	if (literal->index == 0) // check if pipe has no args to the left
		return (literal_error_handling(literal, "Pipe left empty\n", 2));
	if (isredir(literal->array[literal->index - 1][0]))
		return (literal_error_handling(literal, "Argument to left of pipe\n", 2));
}

void	literal_check_errors(t_literal *literal)
{
	literal->index = 0;
	while (literal->array[literal->index])
	{
		if (isredir(literal->array[literal->index][0]))
		{
			literal->type = literal->array[literal->index][0];
			if (literal->array[literal->index][1] == literal->type)
				check_double_redir_error(literal);
			else if (literal->type == '|')
				check_pipe_error(literal);
			else
				check_single_redir_error(literal);
			if (literal->ret == -1)
				return ;
		}
		literal->index++;
	}
}


char	**literal_tokenization(t_mini *mini)
{
	t_literal	literal;
	
	init_literal_struct(&literal);
	count_literal_string(&literal, mini->message);
	if (!literal.count)
		return (NULL);
	literal.str = malloc(sizeof(char) * literal.count);
	if (!literal.str) // handle later
		return (NULL);
	literal_string_sep(&literal, mini->message);
	if (literal.ret == -1)
		return (free (literal.str), NULL);
	literal.array = ft_split(literal.str, 29);
	if (!literal.array)
		return (free (literal.str), NULL); // handle later
	literal_check_errors(&literal); // check more case later
	if (literal.ret == -1)
		return (free(literal.str), NULL);
	return (free(literal.str), literal.array);
}
