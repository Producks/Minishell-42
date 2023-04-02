/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:32:33 by cperron           #+#    #+#             */
/*   Updated: 2023/04/01 18:36:14 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_cmds(char **tokens, int i)
{
	while (is_redir_2(tokens[i]) == 1 && tokens[i + 2])
		i +=2;
	return (i);
}

int	find_pipe(char **tokens, int i)
{	
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) == 1)
			return(i);
		i++;
	}
	return (0);
}
