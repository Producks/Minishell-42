/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:37:08 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 16:03:51 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 69);
	if (!pwd)
	{
		perror("Minishell");
		return (1);
	}
	printf("%s\n", pwd);
	free (pwd);
	return (SUCCESS);
}
