/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:35:39 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 09:34:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

/* Nice */
int	ft_exit(t_mini *mini)
{
	mini->exit = true;
	return (BUILTIN_SUCCESS);
}
