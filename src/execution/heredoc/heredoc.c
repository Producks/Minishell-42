/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:21:41 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 17:41:26 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/parsing.h"
#include "../execution.h"
#include "../../input/input.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int	redirect_input_from_heredoc(t_mini *mini)
{
	if (!mini->cmds_list->redir_list->tmp_file)
		return (print_ambigous("Minishell: ambiguous redirect\n", 1));
	mini->cmds_list->fd_in = open(mini->cmds_list->redir_list->tmp_file,
			O_RDONLY);
	if (mini->cmds_list->fd_in == FAILURE)
		return (print_errno(1), FAILURE);
	if (dup2(mini->cmds_list->fd_in, STDIN_FILENO) == FAILURE)
		return (print_errno(errno), FAILURE);
	if (close(mini->cmds_list->fd_in) == FAILURE)
		return (print_errno(errno), FAILURE);
	return (SUCCESS);
}

static void	exit_heredoc(t_mini *mini, int exit_status, t_redir *head)
{
	mini->cmds_list->redir_list = head;
	close(mini->fd_in);
	close(mini->fd_out);
	free_linked_list_mini(&mini->head_cmd);
	free_double_array(mini->env_copy);
	free_double_array(mini->current_cmds);
	exit(exit_status);
}

static void	heredoc(t_mini *mini, t_redir *head)
{
	int		open_fd;
	int		ret;

	signals_handler_child(true);
	rl_clear_history();
	open_fd = file_handler(mini);
	if (open_fd == FAILURE)
		exit_heredoc(mini, errno, head);
	ret = write_to_heredoc(mini, open_fd);
	exit_heredoc(mini, ret, head);
}

static int	heredoc_fork(t_mini *mini, t_redir *head)
{
	pid_t	child;
	int		ret_status;
	char	file_name[15];

	child = fork();
	if (child == FAILURE)
		return (print_errno(errno), SUCCESS);
	if (child == SUCCESS)
		heredoc(mini, head);
	signals_handler_parent(true, false);
	waitpid(child, &ret_status, 0);
	signals_handler_parent(false, false);
	g_exit_status = calculate_exit_status(ret_status);
	if (g_exit_status == 130 || g_exit_status == ENOMEM)
		return (unlink_temp_file(mini), FAILURE);
	mini->cmds_list->tmp_file = true;
	create_file_name(file_name, mini->cmds_list->count);
	mini->cmds_list->redir_list->tmp_file = ft_strdup(file_name);
	if (!mini->cmds_list->redir_list->tmp_file)
		return (unlink_temp_file(mini), print_errno(ENOMEM), FAILURE);
	return (SUCCESS);
}

int	check_if_heredoc(t_mini *mini)
{
	t_redir	*head;
	int		count;
	int		ret;

	count = 0;
	ret = 0;
	while (mini->cmds_list)
	{
		mini->cmds_list->count = count;
		head = mini->cmds_list->redir_list;
		while (mini->cmds_list->redir_list)
		{
			if (mini->cmds_list->redir_list->type == 54 && count <= 99)
				ret = heredoc_fork(mini, head);
			if (ret == FAILURE)
				return (FAILURE);
			mini->cmds_list->redir_list = mini->cmds_list->redir_list->next;
		}
		count++;
		mini->cmds_list->redir_list = head;
		mini->cmds_list = mini->cmds_list->next;
	}
	mini->cmds_list = mini->head_cmd;
	return (SUCCESS);
}
