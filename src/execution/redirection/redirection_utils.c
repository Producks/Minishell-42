/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:16:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 03:53:50 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	restore_parent_file_descriptors(t_mini *mini)
{
	if (dup2(mini->fd_in, STDIN_FILENO) == FAILURE)
		print_errno(errno);
	if (dup2(mini->fd_out, STDOUT_FILENO) == FAILURE)
		print_errno(errno);
}

static int	handle_out_redirection(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
		ret = redirect_output_to_pipe(mini);
	else if (mini->cmds_list->redir_list->type == READ_OUTPUT)
		ret = redirect_output_to_file(mini);
	else
		ret = redirect_output_append_to_file(mini);
	return (ret);
}

static int	handle_in_redirection(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
		ret = redirect_input_to_pipe(mini);
	else if (mini->cmds_list->redir_list->type == READ_INPUT)
		ret = redirect_input_from_file(mini);
	else
		ret = redirect_input_from_heredoc(mini);
	return (ret);
}

int	handle_io_redirections(t_mini *mini)
{
	int		ret;
	t_redir	*head;

	ret = SUCCESS;
	head = mini->cmds_list->redir_list;
	while (mini->cmds_list->redir_list != NULL)
	{
		if (mini->cmds_list->redir_list->in == true)
			ret = handle_in_redirection(mini);
		if (mini->cmds_list->redir_list->out == true && ret != FAILURE)
			ret = handle_out_redirection(mini);
		if (ret == FAILURE)
			break ;
		mini->cmds_list->redir_list = mini->cmds_list->redir_list->next;
	}
	mini->cmds_list->redir_list = head;
	return (ret);
}
