/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:27:12 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 17:04:36 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	print_error(const char *message, int error_nbr)
{
	perror(message);
	g_exit_status = error_nbr;
	return (FAILURE);
}

void	print_errno(int error_nbr)
{
	perror("Minishell");
	g_exit_status = error_nbr;
}

void	print_string_error(const char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
}

int	print_errno_ret(int error_nbr)
{
	perror("Minishell");
	g_exit_status = error_nbr;
	return (FAILURE);
}
