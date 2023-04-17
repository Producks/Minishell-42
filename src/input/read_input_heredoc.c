/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:59:13 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 11:03:19 by ddemers          ###   ########.fr       */
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

static int	handle_message_error(t_mini *mini)
{
	if (g_exit_status == 6969)
		return (1);
	if (errno == ENOMEM)
		return (print_errno(errno), errno);
	write(STDERR_FILENO,
		"Minishell: warning: here-document by end-of-file (wanted `", 58);
	write(STDERR_FILENO,
		mini->cmds_list->redir_list->filename,
		ft_strlen(mini->cmds_list->redir_list->filename));
	write(STDERR_FILENO, "')\n", 3);
	return (SUCCESS);
}

int	write_to_heredoc(t_mini *mini, int fd)
{
	char			*message;
	char			*expanded_message;
	struct stat		file_status;
	int				ret;

	while (true)
	{
		message = readline("Heredoc > ");
		if (!message)
			return (close(fd), handle_message_error(mini));
		if (!ft_strcmp(mini->cmds_list->redir_list->filename, message))
			break ;
		expanded_message = handle_dollar_heredoc(mini, message);
		if (!expanded_message)
			return (free(message), close(fd), errno);
		free (message);
		if (get_file_status(mini, fd, &file_status) == FAILURE)
			return (free(expanded_message), close(fd), 1);
		write(fd, expanded_message, ft_strlen(expanded_message));
		write(fd, "\n", 1);
		free(expanded_message);
	}
	return (free (message), close(fd), SUCCESS);
}
