/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:02:18 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/15 22:25:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


int	count_number_literal(const char *str)
{
	int		index;
	int		count;
	char	flag;

	index = 0;
	count = 0;
	while (str[index])
	{
		while (str[index] == ' ' && str[index])
			index++;
		if (!str[index])
			break ;
		if (str[index])
		//	count += ;
		while (str[index] && str[index] != ' ')
			index++;
	}
	return (count);
}

char	**literal_tokenization(t_mini *mini)
{
	char	**array;
	int		count;
	
	if (!mini->cmd)
		return (NULL);
	count = count_number_literal(mini->cmd);
	return (array);
}