/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/12 23:35:21 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	read_input(t_mini *mini)
{
	while (true)
	{
		if (g_exit_status == 69)
		{
			g_exit_status = SUCCESS;
			break ;
		}
		mini->message = readline(GRN "Minishell > " RESET);
		if (!mini->message)
		{
			if (errno == ENOMEM)
				g_exit_status = 1;
			break ;
		}
		lexer(mini);
		add_history(mini->message);
		free (mini->message);
		mini->message = NULL;
	}
	rl_clear_history();
	return (SUCCESS);
}
