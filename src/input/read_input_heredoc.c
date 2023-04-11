/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 13:59:46 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	write_to_heredoc(t_mini *mini, int fd)
{
	char			*message;
	struct stat		file_status;
	int				ret;

	while (true)
	{
		message = readline(MAG "Heredoc > " RESET);
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
