/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 14:56:20 by ddemers          ###   ########.fr       */
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
		signals_handler(true, false, true);
		mini->message = readline(GRN "Minishell > " RESET);
		signals_handler(true, false, false);
		//mini->message = readline("Minishell > ");
		if (!mini->message)
		{
			if (errno == ENOMEM)
				g_exit_status = ENOMEM;
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
