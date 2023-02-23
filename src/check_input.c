/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:47:59 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/23 15:41:53 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../lib/Libft-42/libft.h"
#include "pipex.h"
#include "cmds/echo.h"
#include "cmds/pwd.h"


int check_input(char *message, char *envp[])
{
	if (ft_strncmp(message, "exit", 5) == 0)
	{
		return (0);
	}
	else
	{
		//char **test = ft_split(message, ' ');
		pwd();
		return (1);
	}
}