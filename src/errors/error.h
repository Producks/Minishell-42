/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:18:19 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/25 15:17:07 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SUCCESS 0
# define FAILURE -1
# define ENOMEM 12

# include <stdio.h>

extern int	g_exit_status;

int		print_error(const char *message, int error_nbr);
void	print_errno(int error_nbr);

#endif