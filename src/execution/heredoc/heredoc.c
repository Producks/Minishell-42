/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:21:41 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/27 14:33:36 by ddemers          ###   ########.fr       */
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
	open_fd = open("MiniHeredoc", O_CREAT | O_WRONLY | O_APPEND, 0644);
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
	close(fd);
	return (SUCCESS);
}

static int	restore_stdin_fileno(t_mini *mini)
{
	if (mini->fd_in == mini->cmds_list->fd_in)
		return (SUCCESS);
	if (dup2(mini->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	pipe_heredoc(t_mini *mini)
{
	int		open_fd;
	int		ret;

	if (restore_stdin_fileno(mini) == FAILURE)
		return (FAILURE);
	open_fd = file_handler(mini);
	if (open_fd == FAILURE)
		return (FAILURE); //handle later
	ret = write_to_heredoc(mini, open_fd);
	mini->cmds_list->fd_in = open("MiniHeredoc", O_RDONLY);
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}


// static int	heredoc_error_handle(int errnbr)
// {
// 	printf("Don't chmod my file or delete my file😡\n");
// 	return (FAILURE);
// }

// static int	file_handler(t_mini *mini)
// {
// 	int	open_fd;
// 	int	ret;

// 	if (!access("MiniHeredoc", F_OK))
// 	{
// 		ret = unlink("MiniHeredoc");
// 		if (ret == FAILURE)
// 			return (FAILURE);
// 	}
// 	open_fd = open("MiniHeredoc", O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	return (open_fd);
// }

// static int	restore_stdin_fileno(t_mini *mini)
// {
// 	if (mini->fd_in == mini->cmds_list->fd_in)
// 		return (SUCCESS);
// 	if (dup2(mini->fd_in, STDIN_FILENO) == FAILURE)
// 		return (FAILURE);
// 	return (SUCCESS);
// }

// static int	write_to_heredoc(t_mini *mini, int fd)
// {
// 	char	*message;
// 	int		ret;

// 	ret = 0;
// 	while (true)
// 	{
// 		message = readline(MAG "🤡Heredoc > " RESET);
// 		if (!message)
// 			break ;
// 		if (!ft_strcmp(mini->cmds_list->redir_list->filename, message))
// 			break ;
// 		ret = write(fd, message, ft_strlen(message));
// 		ret = write(fd, "\n", 1);
// 		if (ret == FAILURE)
// 			return (heredoc_error_handle(69));
// 		if (ret == FAILURE)
// 			return (heredoc_error_handle(69));
// 		free (message);
// 	}
// 	free (message);
// 	if ((close(fd)) == FAILURE)
// 		return (heredoc_error_handle(69));
// 	return (SUCCESS);
// }

// int	pipe_heredoc(t_mini *mini)
// {
// 	int		open_fd;
// 	int		ret;

// 	if (restore_stdin_fileno(mini) == FAILURE)
// 		return (FAILURE);
// 	open_fd = file_handler(mini);
// 	if (open_fd == FAILURE)
// 		return (FAILURE); //handle later
// 	ret = write_to_heredoc(mini, open_fd);
// 	mini->cmds_list->fd_in = open("MiniHeredoc", O_RDONLY);
// 	if (mini->cmds_list->fd_in == FAILURE)
// 		return (heredoc_error_handle(69));
// 	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
// 		return (FAILURE);
// 	if (close(mini->cmds_list->fd_in) == FAILURE)
// 		return (FAILURE);
// 	return (SUCCESS);
// }
