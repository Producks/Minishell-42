/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:37:08 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 22:01:06 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 69); //check bug fuck
	if (!pwd)
	{
		perror("Minishell");
		return (1);
	}
	printf("%s\n", pwd);
	free (pwd);
	return (SUCCESS);
}
