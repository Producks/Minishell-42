/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:20 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/01 05:53:17 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../struct.h"

/*Check later if this works*/
int	env(t_dlist	*env_list)
{
	while (env_list)
	{
		printf("%s\n", (char *)env_list->data);
		env_list = env_list->next;
	}
	return (0);
}