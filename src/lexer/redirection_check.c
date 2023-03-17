/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:43:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/17 08:43:33 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

extern int	g_exit_status;

int	error_handling(const char *str, int error_nbr)
{
	write(2, str, ft_strlen(str));
	//g_exit_status = error_nbr;
	return (-1);
}

static int	is_redirection(const char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_redir_token(const char *str)
{
	int		index;
	char	type;

	index = 1;
	type = *str;
	while (isspace(str[index]))
		index++;
	if (!str[index])
		return (error_handling("minishell: syntax error near unexpected token `newline'\n", 2));
	if (index != 1 && is_redirection(str[index]))
		return (error_handling("minishell: incorrect input after token\n", 2));
	if (is_redirection(str[index]) && str[index] != type)
		return (error_handling("minishell: incorrect input after token\n", 2));
	if (!is_redirection(str[index]))
		return (1);
	index++;
	while (isspace(str[index]))
		index++;
	if (!str[index])
		return (error_handling("minishell: syntax error near unexpected token `newline'\n", 2));
	if (is_redirection(str[index]))
		return (error_handling("minishell: incorrect input after token\n", 2));
	return (1);
}

int	check_pipe_token(const char *str)
{
	int		index;

	index = 1;
	while (isspace(str[index]))
		index++;
	if (!str[index]) // check if we handle it later
		return (error_handling("minishell: syntax error near unexpected token `newline'\n", 2));
	if (str[index] == '|')
		return (error_handling("minishell: syntax error near unexpected token `|'\n", 2));
	return (1);
}

/*check error message later should be good to go for now, more polish needed later*/
void	redirection_check(t_literal *literal, const char *str)
{
	if (!is_redirection(*str))
	{
		literal->ret = 0;
		return ;
	}
	if (*str == '|')
	{
		literal->ret = check_pipe_token(str);
		if (literal->ret == -1)
			literal->count = -1;
		return ;
	}
	literal->ret = check_redir_token(str);
	if (literal->ret == -1)
		literal->count = -1;
}
