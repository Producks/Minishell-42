/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/30 19:01:50 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>

#ifdef __linux__
# include <sys/types.h>
# include <sys/wait.h>
#endif

# include "../../libs/Libft/libft.h"
# include "../main/struct.h"
# include "../utils/utils.h"
# include "../errors/error.h"

# define SUCCESS 0
# define FAILURE -1

# define REDIRECTION_PIPE 50 // good
# define READ_INPUT 52 
# define READ_OUTPUT 51
# define APPEND_OUT 54
# define APPEND_IN 53


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

/*heredoc.c*/
int		pipe_heredoc(t_mini *mini);

/*heredoc_file_handler.c*/
int		file_handler(t_mini *mini);
int		get_file_status(int fd, struct stat *file_status);

/*heredoc_fd_utils.c*/
int		check_fd_heredoc(t_mini *mini);
int		restore_previous_stdout_fileno(t_mini *mini);

/*heredoc_error_handler.c*/
int	handle_file_handle_error(t_mini *mini);

/*child.c*/
int		create_child_process(t_mini *mini);
void	wait_for_child_process(t_cmds *cmds);

/*path.c*/
char	*find_path(t_mini *mini);

/*execve.c*/
void	run_cmd(t_mini *mini);

/*builtin.c*/
bool	check_if_builtin(t_mini *mini);
int		built_ins(t_mini *mini);

#endif