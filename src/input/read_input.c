/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 17:16:30 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//mini->message = readline("Minishell > ");
int	read_input(t_mini *mini)
{
	while (true)
	{
		if (mini->exit == true)
			return (g_exit_status);
		signals_handler_parent(false, true);
		mini->message = readline(GRN "Minishell > " RESET);
		signals_handler_parent(false, false);
		if (!mini->message)
		{
			if (errno == ENOMEM)
				return (ENOMEM);
			break ;
		}
		add_history(mini->message);
		lexer(mini);
		free (mini->message);
		mini->message = NULL;
	}
	return (g_exit_status);
}
