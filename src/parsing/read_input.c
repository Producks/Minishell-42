/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/23 11:56:25 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	read_input(t_mini *mini)
{
	while (1)
	{
		mini->message = readline(GRN "Minishell > " RESET);
		add_history(mini->message);
		if (g_exit_status == 69)
			break ;
		lexer(mini);
		free (mini->message);
		mini->message = NULL;
	}
	//rl_clear_history();
	return (SUCCESS);
}
