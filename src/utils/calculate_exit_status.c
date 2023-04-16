/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:43:19 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/15 11:48:47 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "utils.h"

int	calculate_exit_status(int exit_status)
{
	int	result;

	if (WIFEXITED(exit_status))
		result = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		result = (128 + WTERMSIG(exit_status));
	return (result);
}
