/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:18:19 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/29 00:50:40 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SUCCESS 0
# define FAILURE -1
# define GENERAL_ERROR 1
# define MISUSE 2
# define COMMAND_NOT_FOUND 127

# include <stdio.h>
# include <errno.h>
# include "../../libs/Libft/libft.h"

extern int	g_exit_status;

int		print_error(const char *message, int error_nbr);
void	print_errno(int error_nbr);
void	print_string_error(const char *message);

#endif