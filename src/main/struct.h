/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:26:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/29 01:33:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef STRUCT_H
# define STRUCT_H

# include "../../libs/Libft/libft.h"
# include <stdbool.h>

typedef struct s_redirect
{
    char				*filename;
	bool				in;
	bool 				out;
    int					type;
    struct s_redirect	*next;
	struct s_redirect	*head;
}	t_redir;

// linked list of commands example listed in comments of how a node would look like
typedef struct s_cmds
{
	char			**cmds; // {echo, hello, NULL} {cat,}
	char			*path;
	int				fd_in;
	int				fd_out;
	bool			fd_out_bool;
	t_redir			*redir_list;
	pid_t			pid;
	struct s_cmds	*previous;
	struct s_cmds	*next;
	struct s_cmds	*head; // why is there an head
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
	char	**literal_token;
	int		fd_in;
	int		fd_out;
}	t_mini;

#endif