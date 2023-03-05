/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 07:45:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/05 07:55:13 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "../main/struct.h"
#include "read_input.h"
#include "check_input.h"

int	read_input(t_mini *mini)
{
	printf(GRN "Minishell >" RESET);
	if (!mini->message)
		mini->message = readline(" ");
	while (check_input(mini) != 0)
	{
		free (mini->message);
		printf(GRN "Minishell >" RESET);
		mini->message = readline(" ");
	}
	return (0);
}