/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:26:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/05 11:00:32 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../../libs/Libft/libft.h"

typedef struct s_cmds
{
	char	**cmds;
	char	*path;
	int		in;
	int		out;
}	t_cmds;

typedef struct s_mini
{
	t_dlist	*tokens;
	char	**env_copy;
	char 	*message;
	char	**cmd;
}	t_mini;

#endif