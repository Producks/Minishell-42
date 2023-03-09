/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:37 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/08 13:56:17 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h> //linux only for wait and waitpid
# include <sys/wait.h> //linux only for wait and waitpid
# include "../../libs/Libft/libft.h"
# include "../main/struct.h"
# include "../utils/utils.h"
# include <fcntl.h>

# define READ_PIPE 0
# define WRITE_PIPE 1

# define REDIRECTION_PIPE = 50
# define RED_INPUT = 51
# define RED_OUTPUT = 52
# define RED_APPEND_OUT 53
# define RED_APPEND_IN 54

void	make_child(int nbr, char *message, char *envp[]);
void	create_child(char *message, char *envp[]);
void	create_fork(t_mini *mini);
int		pipe_redirection(t_mini *mini);
void	pipe_restore(t_mini *mini, int in, int out);

#endif