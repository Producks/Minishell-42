/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:26:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 20:03:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <unistd.h>
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
	char			**cmds;
	char			*path;
	int				nb_cmds;
	int				fd_in;
	int				fd_out;
	bool			fd_out_bool;
	t_redir			*redir_list;
	pid_t			pid;
	bool			tmp_file;
	int				count;
	bool			skip;
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
	char	*current_dir;
	int		fd_in;
	int		fd_out;
	bool	is_one_cmd;
	bool	skip_waiting;
	bool	exit;
}	t_mini;

#endif