/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:26:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/12 17:13:16 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../../libs/Libft/libft.h"

// linked list of commands example listed in comments of how a node would look like
typedef struct s_cmds
{
	char			**cmds; // {"cat" , NULL};
	char			*path; // "bin/ls"; Parsing doesn't have to worry about this one
	int				fd_in; //  Parsing doesn't have to worry about this one, for execution, store the fd for pipes
	int				fd_out; //  Parsing doesn't have to worry about this one, for execution, store the fd for pipes
	int				in_type; // Type of redirection, > < >> << |, have to come up with the way we want to do it
	int				out_type; // Type of redirection, > < >> << |, have to come up with the way we want to do it
	char			*infile; /*For < <<, store the name of the file. If < was the infile redirection, here an example and what it would store from the example. file1.txt < cat | wc. This would store file1.txt has a string */
	char			*outfile; // Same thing from infile, but for the > >>
	pid_t			pid; //child pid for execution only
	struct s_cmds	*previous; // Point to previous node, function that create the node deal with it
	struct s_cmds	*next; // Point to next node, function that create the node deal with it
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