/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/14 14:13:33 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

#ifdef __linux__
# include <sys/types.h>
# include <sys/wait.h>
#endif

# include "../../libs/Libft/libft.h"
# include "../main/struct.h"
# include "../utils/utils.h"

# define SUCCESS 0
# define FAILURE -1

# define REDIRECTION_PIPE 50
# define READ_INPUT 51
# define READ_OUTPUT 52
# define APPEND_OUT 53
# define APPEND_IN 54

void	create_child_process(t_mini *mini);
void	handle_cmds(t_mini *mini);

/*Functions of heredoc.c*/
int		pipe_heredoc(t_mini *mini);

/*Functions of path.c*/
char	*find_path(t_mini *mini);

/*Functions of redirection.c*/
int		handle_redirections(t_mini *mini);
void	restore_parent_fds(t_mini *mini);
int		redirect_in_to_pipe(t_mini *mini);
int		redirect_out_to_pipe(t_mini *mini);
int		redirect_input(t_mini *mini);
int		redirect_output(t_mini *mini);
int		redirect_output_append(t_mini *mini);

#endif