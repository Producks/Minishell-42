/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:47:59 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/28 13:58:05 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../../lib/libft.h"
#include "../pipex.h"
#include "../cmds/cmds.h"

int	check_if_utils(char *message, char *envp[])
{
	if (ft_strncmp(message, "echo", 4) == 0)
		echo(NULL); // to do
	else if (ft_strncmp(message, "cd", 2) == 0)
		cd("test"); // to do
	else if (ft_strncmp(message, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(message, "export", 6) == 0)
		export(); // to do
	else if (ft_strncmp(message, "unset", 5) == 0)
		unset(); // to do
	else if (ft_strncmp(message, "env", 3) == 0)
		env(envp); // to do
	else if (ft_strncmp(message, "exit", 4) == 0)
		ft_exit(); // to do
	return (1);
}

int check_input(char *message, char *envp[])
{
	if (check_if_utils(message, envp) == 1)
		return (1);
	else
		create_child(message, envp);
	return (1);
}
