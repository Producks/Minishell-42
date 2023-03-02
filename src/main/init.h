/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:33:47 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/28 10:01:34 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
#define INIT_H

#include "struct.h"

int		init_struct(t_mini *mini, char *envp[]);
void	free_struct(t_mini *mini);

#endif