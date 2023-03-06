/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:26:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/06 11:17:21 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../../libs/Libft/libft.h"

// linked list of commands
typedef struct s_cmds
{
	char			**cmds;
	char			*path;
	int				in;
	int				out;
	char			*infile;
	char			*outfile;
	struct s_cmds	*previous;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_mini
{
	t_cmds	*cmds_link_test;
	t_dlist	*tokens;
	char	**env_copy;
	char 	*message;
	char	**cmd;
}	t_mini;

#endif