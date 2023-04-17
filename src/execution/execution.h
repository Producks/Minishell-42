/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 14:20:06 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include <sys/stat.h>

# ifdef __linux__
#  include <sys/types.h>
#  include <sys/wait.h>
# endif

# include "../utils/utils.h"

/*execution.c*/

void	execution(t_mini *mini);

/*path.c*/

char	*find_path(t_mini *mini);

/*redirection_utils.c*/

int		handle_io_redirections(t_mini *mini);
void	restore_parent_file_descriptors(t_mini *mini);

/*io_redirection.c*/

int		redirect_input_from_file(t_mini *mini);
int		redirect_output_to_file(t_mini *mini);
int		redirect_output_append_to_file(t_mini *mini);
int		redirect_output_to_pipe(t_mini *mini);
int		redirect_input_to_pipe(t_mini *mini);
int		redirect_input_from_heredoc(t_mini *mini);

/*heredoc.c*/

int		check_if_heredoc(t_mini *mini);

/*heredoc_file_handler.c*/

int		file_handler(t_mini *mini);
int		get_file_status(t_mini *mini, int fd, struct stat *file_status);
void	unlink_temp_file(t_mini *mini);

/*child.c*/

int		create_child_process(t_mini *mini);
void	wait_for_child_process(t_cmds *cmds, bool skip_waiting);

/*path.c*/

char	*find_path(t_mini *mini);

/*execve.c*/

void	run_cmd(t_mini *mini);

/*builtin.c*/

bool	check_if_builtin(t_mini *mini);
int		built_ins(t_mini *mini);

/*Cleanup.c*/

void	child_cleanup_command_not_found(t_mini *mini);
void	child_cleanup_execve_failure(t_mini *mini);
void	child_cleanup_no_cmds(t_mini *mini);
void	cleanup(t_mini *mini);

#endif