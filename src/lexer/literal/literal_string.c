/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:02:23 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 01:09:22 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static void	check_quotes_literal(t_literal *literal, const char *str)
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
