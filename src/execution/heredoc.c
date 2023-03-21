/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:21:41 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/21 19:03:12 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"
#include "execution.h"
#include <unistd.h>
#include <fcntl.h>

int	pipe_heredoc(t_mini *mini)
{
	char buffer[] = "exit";
	char buffer_two[50000];
	char *message;
	int	fd[2];
	int	ret;
	int open_fd;

	ret = 0;
	ret = pipe(fd);
	if (ret == -1)
		return (FAILURE);
	open_fd = open(".temp", O_CREAT | O_WRONLY | O_APPEND, 0644);
	printf("%d\n", open_fd);
	message = readline(MAG "🤡Heredoc > " RESET);
	write(open_fd, message, ft_strlen(message));
	write(open_fd, "\n", 1);
	//while (ft_strcmp("TEST", mini->cmds_list->redir_list->filename))
	while (ft_strcmp(buffer, message))
	{
		free(message);
		message = readline(MAG "🤡Heredoc > " RESET);
		write(open_fd, message, ft_strlen(message));
		write(open_fd, "\n", 1);
	}
	unlink(".temp");
	return (SUCCESS);
}