/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:18:19 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 14:17:36 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../utils/common_definitons.h"
# include <stdio.h>
# include <errno.h>
# include "../../libs/Libft/libft.h"

extern int	g_exit_status;

int		print_error(const char *message, int error_nbr);
void	print_errno(int error_nbr);
void	print_string_error(const char *message);
int		print_errno_ret(int error_nbr);
int		print_ambigous(const char *message, int error_nbr);

#endif