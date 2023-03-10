/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/10 17:00:59 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

#ifdef __linux__
# include <sys/types.h>
# include <sys/wait.h>
#endif

# include "../../libs/Libft/libft.h"
# include "../main/struct.h"
# include "../utils/utils.h"

# define READ_PIPE 0
# define WRITE_PIPE 1

# define REDIRECTION_PIPE 50
# define READ_INPUT 51
# define READ_OUTPUT 52
# define READ_APPEND_OUT 53
# define READ_APPEND_IN 54

void	make_child(int nbr, char *message, char *envp[]);
void	create_child(char *message, char *envp[]);
void	create_fork(t_mini *mini);
int		pipe_redirection(t_mini *mini);
void	pipe_restore(t_mini *mini);
int		close_pipes_subroutine(t_mini *mini);

#endif