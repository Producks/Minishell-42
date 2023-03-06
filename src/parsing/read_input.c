/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/06 07:44:09 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// #include "../../libs/readline/readline.h"
// #include "../../libs/readline/history.h"
#include "../main/struct.h"
#include "read_input.h"
#include "check_input.h"

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
	return (0);
}