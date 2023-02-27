/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:47:59 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 12:05:20 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../lib/Libft-42/libft.h"
#include "pipex.h"
#include "cmds/cmds.h"

int	check_if_utils(char *message, char *envp[])
{
	if (ft_strncmp(message, "pwd", 3) == 0)
	{
		pwd();
		return (0);
	}
	else if (ft_strncmp(message, "env", 3) == 0)
	{
		env(envp);
		return (0);
	}
	else if (ft_strncmp(message, "echo", 4) == 0)
	{
		//echo("test"); // to do	
	}
	return (1);
}

int check_input(char *message, char *envp[])
{
	if (ft_strncmp(message, "exit", 5) == 0)
	{
		return (0);
	}
	else
	{
		if (check_if_utils(message, envp) == 1)
			create_child(message, envp);
		return (1);
	}
}