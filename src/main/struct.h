/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:26:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/13 13:16:43 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../../libs/Libft/libft.h"

// linked list of commands example listed in comments of how a node would look like
typedef struct s_cmds
{
	char			**cmds;
	char			*path;
	int				fd_in;
	int				fd_out;
	int				in_type;
	int				out_type;
	char			*infile;
	char			*outfile;
	pid_t			pid;
	struct s_cmds	*previous;
	struct s_cmds	*next;
}	t_cmds;

/*
Temp table of in and out type
None:0
|: 50
>: 51
<: 52
>>: 53
<<: 54
*/

typedef struct s_mini
{
	t_cmds	*cmds_list;
	char	**env_copy;
	char 	*message;
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_mini;

#endif