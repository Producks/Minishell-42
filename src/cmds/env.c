/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:20 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/12 14:12:38 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

/*Check later if this works*/
int	env(char **env_copy)
{
	while (*env_copy)
		printf("%s\n", *env_copy++);
	return (BUILTIN_SUCCESS);
}
