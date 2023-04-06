/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:20:11 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/06 15:05:01 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	file_handler(t_mini *mini)
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
	if (open_fd == FAILURE)
		return (FAILURE); // handle later
	mini->delete_file = true;
	return (open_fd);
}

int	get_file_status(int fd, struct stat *file_status)
{
	int		ret;
	mode_t file_chmod;

	ret = fstat(fd, file_status);
	if (ret == -1)
	{
		return (FAILURE); // perror later
	}
	file_chmod = file_status->st_mode & 07777;
	if (file_chmod != 0644)
	{
		printf("Bozo don't chmod my file wtf\n");
		return (FAILURE);
	}
	if (access("MiniHeredoc", F_OK) == FAILURE)
	{
		printf("Bozo can you not delete my file?\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
