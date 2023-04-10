/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:21:41 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/07 11:57:45 by ddemers          ###   ########.fr       */
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
		if (get_file_status(mini, fd, &file_status) == FAILURE)
			return (free(message), close(fd), FAILURE);
		write(fd, message, ft_strlen(message));
		write(fd, "\n", 1);
		free (message);
	}
	free (message);
	close(fd);
	return (SUCCESS);
}

static int	heredoc(t_mini *mini)
{
	int		open_fd;
	int		ret;

	open_fd = file_handler(mini);
	if (open_fd == FAILURE)
		return (FAILURE);
	ret = write_to_heredoc(mini, open_fd);
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	check_if_heredoc(t_mini *mini)
{
	t_redir	*head;
	int		count;

	mini->head_cmd = mini->cmds_list;
	count = 0;
	while (mini->cmds_list)
	{
		mini->cmds_list->count = count;
		head = mini->cmds_list->redir_list;
		while (mini->cmds_list->redir_list)
		{
			if (mini->cmds_list->redir_list->type == 54 && count <= 99)
			{
				heredoc(mini);
				mini->cmds_list->tmp_file = true;
			}
			mini->cmds_list->redir_list = mini->cmds_list->redir_list->next;
		}
		count++;
		mini->cmds_list->redir_list = head;
		mini->cmds_list = mini->cmds_list->next;
	}
	mini->cmds_list = mini->head_cmd;
}
