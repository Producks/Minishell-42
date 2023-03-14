/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/14 12:35:01 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "execution.h"
#include "../cmds/cmds.h"


t_cmds	*generate_cmds(t_mini *mini, int flag)
{
	t_cmds	*cmds;
	t_redir	*redir;

	cmds = create_node_cmds();
	redir = create_node_redir();
	if (flag == 0)
	{
		cmds->cmds = ft_split("cat", ' ');
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
		redir->out = true;
		redir->type = READ_OUTPUT;
		redir->filename = ft_strdup("test1");
		t_redir *redir2;
		redir2 = create_node_redir();
		redir2->out = true;
		redir->type = APPEND_IN;
		redir2->filename = ft_strdup("test2");
		add_node_redir(&redir ,redir2);
		t_redir *redir3;
		redir3 = create_node_redir();
		redir3->in = true;
		redir3->type = READ_INPUT;
		redir3->filename = ft_strdup("Makefile");
		add_node_redir(&redir, redir3);
		t_redir *redir4;
		redir4 = create_node_redir();
		redir4->in = true;
		redir4->type = READ_INPUT;
		redir4->filename = ft_strdup("input.txt");
		add_node_redir(&redir, redir4);
	}
	else if (flag == 1)
	{
		cmds->cmds = ft_split("grep 9", ' ');
		//cmds->outfile = ft_strdup("output.txt");
		// cmds->in_type = REDIRECTION_PIPE;
		// cmds->out_type = 0;
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
	}
	else
	{
		cmds->cmds = ft_split("echo hello", ' ');
		// cmds->in_type = REDIRECTION_PIPE;
		// cmds->out_type = REDIRECTION_PIPE;
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
		// redir->in = true;
		// redir->type = REDIRECTION_PIPE;
		//free_linked_list_redir(&mini->cmds_list->redir_list);
	}
	cmds->redir_list = redir;
	return (cmds);
}

void	generate_test_env(t_mini *mini)
{
	t_cmds	*cmds;
	t_cmds	*cmds_2;
	t_cmds	*cmds_3;

	cmds = generate_cmds(mini, 0);
	//cmds_2 = generate_cmds(mini, 2);
	//cmds_3 = generate_cmds(mini, 1);
	add_node_cmds(&mini->cmds_list, cmds);
	//add_node_cmds(&mini->cmds_list, cmds_2);
	//add_node_cmds(&mini->cmds_list, cmds_3);
}

int	check_if_built_ins(t_mini *mini)
{
	if (ft_strcmp(mini->cmds_list->cmds[0], "echo") == 0)
		return (echo(mini->cmds_list->cmds)); 
	// else if (ft_strcmp(mini->cmd[0], "cd") == 0)
	// 	cd(mini);
	// else if (ft_strcmp(mini->cmd[0], "pwd") == 0)
	// 	pwd();
	// else if (ft_strcmp(mini->cmd[0], "export") == 0)
	// 	ft_export(mini);
	// else if (ft_strcmp(mini->cmd[0], "unset") == 0)
	// 	unset(mini);
	// else if (ft_strcmp(mini->cmd[0], "env") == 0)
	// 	env(mini->env_copy);
	// else if (ft_strcmp(mini->cmd[0], "exit") == 0)
	// 	ft_exit(mini);
	return (1);
}

void	run_cmd(t_mini *mini)
{
	char	*path;
	int		index;
	char	*test;

	index = 0;
	// if (check_if_built_ins(mini))
	// 	exit (0);
	//check_if_executable(mini);
	path = find_path(mini);
	mini->cmds_list->cmds[0] = path; //leaks
	execve(path, mini->cmds_list->cmds, mini->env_copy);
	exit(0);
}

void	wait_for_child_process(t_cmds *cmds)
{
	while (cmds)
	{
		waitpid(cmds->pid, NULL, 0);
		cmds = cmds->next;
	}
}

/*Will handle errors later prototype to see if the idea works*/
void	create_child_process(t_mini *mini)
{
	t_cmds *head;
	int		ret;

	head = mini->cmds_list;
	while (mini->cmds_list)
	{
		ret = handle_redirections(mini);
		mini->cmds_list->pid = fork();
		if (mini->cmds_list->pid == 0)
			run_cmd(mini);
		mini->cmds_list = mini->cmds_list->next;
		restore_parent_fds(mini);
	}
	mini->cmds_list = head;
}

void	handle_cmds(t_mini *mini)
{
	generate_test_env(mini); // remove later, only used for testing commands without parsing
	create_child_process(mini);
	wait_for_child_process(mini->cmds_list);
	mini->cmds_list = free_linked_list_mini(&mini->cmds_list);
}
