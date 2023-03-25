/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/21 14:18:49 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	read_input(t_mini *mini)
{
	char	*history;

	if (!mini->message)
		mini->message = readline(GRN "Minishell > " RESET);
	add_history(mini->message);
	while (check_input(mini) != 0)
	{
		free (mini->message);
		mini->message = readline(GRN "Minishell > " RESET);
		rl_redisplay();
		add_history(mini->message);
	}
	//rl_clear_history(); // Why doesn't this trash want to compile? garbage fucking mac
	/*Fix found, need to compile real readline library and use that on the school computer
	TODO later*/
	return (0);
}
