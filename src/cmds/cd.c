/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:34:58 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/03 11:34:34 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include <stdio.h>
#include <unistd.h>

static int	cd_error_handler(char *message, int count)
{
	
}

int	cd(char **cmd)
{
	int		ret;
	int		count;
	char	*error;
	
	count = count_double_array(cmd);
	if (count > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (0);
	}
	ret = chdir(*cmd);
	if (ret == -1)
		perror("cd");
	return (0);
}
