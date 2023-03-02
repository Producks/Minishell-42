/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:20 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 12:27:14 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../main/struct.h"

/*Check later if this works*/
int	env(char **env_copy)
{
	while (*env_copy++)
		printf("%s\n", *env_copy);
	return (0);
}