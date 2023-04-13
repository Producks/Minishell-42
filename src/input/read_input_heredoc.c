/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/12 11:40:50 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char	*handle_dollar_heredoc(t_mini *mini, char *message)
{
	char	*expanded_message;

	expanded_message = dollar_interpreter(message, mini);
	if (!expanded_message)
		return (NULL);
	return (expanded_message);
}

int	write_to_heredoc(t_mini *mini, int fd)
{
	char			*message;
	char			*expanded_message;
	struct stat		file_status;
	int				ret;

	while (true)
	{
		message = readline(MAG "Heredoc > " RESET);
		if (!message)
			break ;
		if (!ft_strcmp(mini->cmds_list->redir_list->filename, message))
			break ;
		expanded_message = handle_dollar_heredoc(mini, message);
		if (!expanded_message)
			return (free(message), close(fd), FAILURE);
		free (message);
		if (get_file_status(mini, fd, &file_status) == FAILURE)
			return (free(expanded_message), close(fd), FAILURE);
		write(fd, expanded_message, ft_strlen(expanded_message));
		write(fd, "\n", 1);
	}
	free (message);
	close(fd);
	return (SUCCESS);
}
