/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:43:16 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/15 18:32:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

extern int	g_exit_status;

bool	error_handling(const char *str, int error_nbr)
{
	write(2, str, ft_strlen(str));
	g_exit_status = error_nbr;
	return (false);
}

static bool	is_redirection(const char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

bool	check_redir_token(const char *str)
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
		return (true);
	index++;
	while (isspace(str[index]))
		index++;
	if (!str[index])
		return (error_handling("minishell: syntax error near unexpected token `newline'\n", 2));
	if (is_redirection(str[index]))
		return (error_handling("minishell: incorrect input after token\n", 2));
	return (true);
}

bool	check_pipe_token(const char *str)
{
	int		index;

	index = 1;
	while (isspace(str[index]))
		index++;
	if (!str[index]) // check if we handle it later
		return (error_handling("minishell: syntax error near unexpected token `newline'\n", 2));
	if (str[index] == '|')
		return (error_handling("minishell: syntax error near unexpected token `|'\n", 2));
	return (true);
}

/*check error message later should be good to go for now, more polish needed later*/
bool	redirection_check(const char *str)
{
	if (!is_redirection(*str))
		return (false);
	if (*str == '|')
		return (check_pipe_token(str));
	return (check_redir_token(str));
}