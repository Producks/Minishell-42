/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:21:41 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/31 17:41:20 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/parsing.h"
#include "../execution.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static int	write_to_heredoc(t_mini *mini, int fd)
{
	char			*message;
	struct stat		file_status;
	int				ret;

	while (true)
	{
		message = readline(MAG "🤡Heredoc > " RESET);
		if (!message)
			break ;
		if (!ft_strcmp(mini->cmds_list->redir_list->filename, message))
			break ;
		if (get_file_status(fd, &file_status) == FAILURE)
			return (free(message), close(fd), FAILURE);
		write(fd, message, ft_strlen(message));
		write(fd, "\n", 1);
		free (message);
	}
	free (message);
	close(fd);
	return (SUCCESS);
}

int	pipe_heredoc(t_mini *mini)
{
	int		open_fd;
	int		ret;

	if (check_fd_heredoc(mini) == FAILURE)
		return (FAILURE);
	open_fd = file_handler(mini);
	if (open_fd == FAILURE)
		return (FAILURE); //handle later
	ret = write_to_heredoc(mini, open_fd);
	if (ret == FAILURE)
		return (FAILURE); // handle fd
	mini->cmds_list->fd_in = open("MiniHeredoc", O_RDONLY);
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	restore_previous_stdout_fileno(mini);
	return (SUCCESS);
}