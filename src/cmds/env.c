/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:20 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/27 09:27:15 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*Check later if this works*/
void	env(char *envp[])
{
	char *str;

	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
}