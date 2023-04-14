/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:26:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/13 00:52:06 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../../libs/Libft/libft.h"
# include <stdbool.h>

typedef struct s_redirect
{
	char				*filename;
	char				*tmp_file;
	bool				in;
	bool				out;
	int					type;
	struct s_redirect	*next;
	struct s_redirect	*head;
}	t_redir;

typedef struct s_cmds
{
	char			**cmds; // {echo, hello, NULL} {cat,}
	char			*path;
	int				nb_cmds;
	int				fd_in;
	int				fd_out;
	bool			fd_out_bool;
	t_redir			*redir_list;
	pid_t			pid;
	bool			tmp_file;
	int				count;
	struct s_cmds	*previous;
	struct s_cmds	*next;
	struct s_cmds	*head;
}	t_cmds;

typedef struct s_mini
{
	t_cmds	*cmds_list;
	t_cmds	*head_cmd;
	char	**current_cmds;
	char	**env_copy;
	char	*message;
	int		fd_in;
	int		fd_out;
	bool	is_one_cmd;
	bool	skip_waiting;
	bool	child_fork;
}	t_mini;

#endif