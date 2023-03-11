/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/10 23:50:07 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../cmds/cmds.h"

t_cmds	*generate_cmds(t_mini *mini, int flag)
{
	t_cmds *cmds;

	cmds = create_node_cmds();
	if (flag == 0)
	{
		cmds->cmds = ft_split("cat", ' ');
		//cmds->infile = ft_strdup("input.txt");
		cmds->in_type = 0;
		cmds->out_type = REDIRECTION_PIPE;
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
	}
	else if (flag == 1)
	{
		cmds->cmds = ft_split("wc", ' ');
		//cmds->outfile = ft_strdup("output.txt");
		cmds->in_type = REDIRECTION_PIPE;
		cmds->out_type = 0;
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
	}
	else
	{
		cmds->cmds = ft_split("echo hello", ' ');
		cmds->in_type = REDIRECTION_PIPE;
		cmds->out_type = REDIRECTION_PIPE;
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
	}
	return (cmds);
}

char	*find_path(t_mini *mini)
{
	char	*path;
	char	**path_try;
	int		index;

	index = 0;
	while (mini->env_copy[index] && ft_strncmp(mini->env_copy[index], "PATH=", 5))
		index++;
	if (!mini->env_copy[index])
		return (NULL);
	path_try = ft_split(mini->env_copy[index], ':');
	if (!path_try)
		return (NULL);
	index = 0;
	while (path_try[index])
	{
		path = strjoin_path(path_try[index], mini->cmds_link_test->cmds[0], '/');
		if (!access(path, F_OK))
		{
			ft_free(path_try);
			return (path);
		}
		free(path);
		index++;
	}
	free(path);
	ft_free(path_try);
	return (NULL);
}

void	generate_test_env(t_mini *mini)
{
	t_cmds	*cmds;
	t_cmds	*cmds_2;
	t_cmds	*cmds_3;

	cmds = generate_cmds(mini, 0);
	cmds_2 = generate_cmds(mini, 2);
	cmds_3 = generate_cmds(mini, 1);
	add_node_cmds(&mini->cmds_link_test, cmds);
	add_node_cmds(&mini->cmds_link_test, cmds_2);
	add_node_cmds(&mini->cmds_link_test, cmds_3);
}

int	check_if_built_ins(t_mini *mini)
{
	if (ft_strcmp(mini->cmds_link_test->cmds[0], "echo") == 0)
		return (echo(mini->cmds_link_test->cmds)); 
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
	path = find_path(mini);
	mini->cmds_link_test->cmds[0] = path; //leaks
	execve(path, mini->cmds_link_test->cmds, mini->env_copy);
	exit(0);
}

/*Will handle errors later prototype to see if the idea works*/
void	create_fork(t_mini *mini)
{
	t_cmds *head;
	int		ret;

	generate_test_env(mini);
	head = mini->cmds_link_test;
	while (mini->cmds_link_test)
	{
		ret = pipe_redirection(mini);
		mini->cmds_link_test->pid = fork();
		if (mini->cmds_link_test->pid == 0)
			run_cmd(mini);
		mini->cmds_link_test = mini->cmds_link_test->next;
		pipe_restore(mini);
	}
	mini->cmds_link_test = head;
	while (mini->cmds_link_test)
	{
		waitpid(mini->cmds_link_test->pid, NULL, 0);
		mini->cmds_link_test = mini->cmds_link_test->next;
	}
	mini->cmds_link_test = free_linked_list_mini(&head);
}
