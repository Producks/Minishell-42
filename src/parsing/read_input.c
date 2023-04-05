/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/05 00:47:35 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	read_input(t_mini *mini)
{
	while (true)
	{
		if (g_exit_status == 69)
			break ;
		mini->message = readline(GRN "Minishell > " RESET);
		if (!mini->message)
			break ;
		lexer(mini);
		add_history(mini->message);
		free (mini->message);
		mini->message = NULL;
	}
	rl_clear_history();
	return (SUCCESS);
}
