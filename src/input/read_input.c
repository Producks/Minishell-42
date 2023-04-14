/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 13:36:00 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//mini->message = readline("Minishell > ");
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
