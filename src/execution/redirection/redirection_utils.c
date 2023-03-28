/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:16:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/28 00:20:03 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	restore_parent_file_descriptors(t_mini *mini)
{
	dup2(mini->fd_in, STDIN_FILENO);
	dup2(mini->fd_out, STDOUT_FILENO);
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
		ret = pipe_heredoc(mini);
	return (ret);
}

int	handle_io_redirections(t_mini *mini)
{
	int		ret;
	t_redir	*head;

	ret = 0;
	head = mini->cmds_list->redir_list;
	while (mini->cmds_list->redir_list != NULL)
	{
		if (mini->cmds_list->redir_list->in == true)
			ret = handle_in_redirection(mini);
		if (mini->cmds_list->redir_list->out == true && ret != FAILURE)
			ret = handle_out_redirection(mini);
		if (ret == FAILURE)
		{
			perror("minishell:"); // fix later
			break ;
		}
		mini->cmds_list->redir_list = mini->cmds_list->redir_list->next;
	}
	mini->cmds_list->redir_list = head;
	return (ret);
}

// int	handle_io_redirections(t_mini *mini)
// {
// 	int		ret;
// 	t_redir	*head;

// 	ret = 0;
// 	head = mini->cmds_list->redir_list;
// 	while (mini->cmds_list->redir_list != NULL)
// 	{
// 		if (mini->cmds_list->redir_list->in == true)
// 		{
// 			if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
// 				ret = redirect_input_to_pipe(mini);
// 			else if (mini->cmds_list->redir_list->type == READ_INPUT)
// 				ret = redirect_input_from_file(mini);
// 			else
// 				ret = pipe_heredoc(mini);
// 		}
// 		if (mini->cmds_list->redir_list->out == true && ret != FAILURE)
// 		{
// 			if (mini->cmds_list->redir_list->type == REDIRECTION_PIPE)
// 				ret = redirect_output_to_pipe(mini);
// 			else if (mini->cmds_list->redir_list->type == READ_OUTPUT)
// 				ret = redirect_output_to_file(mini);
// 			else
// 				ret = redirect_output_append_to_file(mini);
// 		}
// 		mini->cmds_list->redir_list = mini->cmds_list->redir_list->next;
// 	}
// 	mini->cmds_list->redir_list = head;
// 	return (ret);
// }