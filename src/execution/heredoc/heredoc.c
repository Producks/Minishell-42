/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:21:41 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/25 10:12:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/parsing.h"
#include "../execution.h"
#include <unistd.h>
#include <fcntl.h>

static int	file_handler(t_mini *mini)
{
	int	open_fd;
	int	ret;

	if (!access("MiniHeredoc", F_OK))
	{
		ret = unlink("MiniHeredoc");
		if (ret == FAILURE)
			return (FAILURE);
	}
	open_fd = open("MiniHeredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	return (open_fd);
}

static int	write_to_heredoc(t_mini *mini, int fd)
{
	char	*message;

	while (true)
	{
		message = readline(MAG "🤡Heredoc > " RESET);
		if (!ft_strcmp(mini->cmds_list->redir_list->filename, message))
			break ;
		write(fd, message, ft_strlen(message));
		write(fd, "\n", 1);
		free (message);
	}
	free (message);
	//close(fd);
	return (SUCCESS);
}

int	pipe_heredoc(t_mini *mini)
{
	int		open_fd;
	int		ret;

	open_fd = file_handler(mini);
	if (open_fd == FAILURE)
		return (FAILURE); //handle later
	ret = write_to_heredoc(mini, open_fd);
	//mini->cmds_list->fd_in = open("MiniHeredoc", O_RDONLY);
	mini->cmds_list->fd_in = open_fd;
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
