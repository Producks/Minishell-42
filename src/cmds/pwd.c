/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:37:08 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 20:19:58 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

int	pwd(t_mini *mini)
{
	char	*pwd;

	if (!mini->current_dir)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (print_errno(errno), BUILTIN_COMMAND_ERROR);
		printf("%s\n", pwd);
		free(pwd);
		return (SUCCESS);
	}
	printf("%s\n", mini->current_dir);
	return (SUCCESS);
}
