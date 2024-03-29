/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:20:11 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 01:56:02 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	unlink_temp_file(t_mini *mini)
{
	char	file_name[15];

	create_file_name(file_name, mini->cmds_list->count);
	if (!access(file_name, F_OK))
		unlink(file_name);
}

int	get_file_status(t_mini *mini, int fd, struct stat *file_status)
{
	int		ret;
	mode_t	file_chmod;

	ret = fstat(fd, file_status);
	if (ret == -1)
		return (print_errno(errno), FAILURE);
	file_chmod = file_status->st_mode & 07777;
	if (file_chmod != 0644)
	{
		write(STDERR_FILENO, "Minishell: Can you not chmod my file?\n", 38);
		return (FAILURE);
	}
	if (access(mini->cmds_list->redir_list->tmp_file, F_OK) == FAILURE)
	{
		write(STDERR_FILENO, "Minishell: Can you not delete my file?\n", 39);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	file_handler(t_mini *mini)
{
	int		open_fd;
	char	file_name[15];
	int		ret;

	create_file_name(file_name, mini->cmds_list->count);
	if (!access(file_name, F_OK))
	{
		ret = unlink(file_name);
		if (ret == FAILURE)
			return (print_errno(errno), FAILURE);
	}
	open_fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (open_fd == FAILURE)
		return (print_errno(errno), FAILURE);
	mini->cmds_list->redir_list->tmp_file = ft_strdup(file_name);
	if (!mini->cmds_list->redir_list->tmp_file)
		return (close(open_fd), print_errno(ENOMEM), FAILURE);
	return (open_fd);
}
