/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/09 17:30:05 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmds	*generate_cmds(t_mini *mini, int flag)
{
	t_cmds *cmds;

	cmds = create_node_cmds();
	if (flag == 0)
	{
		cmds->cmds = ft_split("cat", ' ');
		cmds->infile = ft_strdup("test.txt");
		cmds->in_type = 51;
		cmds->out_type = 50;
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
	}
	else
	{
		cmds->cmds = ft_split("wc", ' ');
		cmds->in_type = 50;
		cmds->out_type = 0;
		cmds->fd_in = mini->fd_in;
		cmds->fd_out = mini->fd_out;
	}
	return (cmds);
}

char	*find_path(t_mini *mini)
{
	char	*path;
	char	*path_2;
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
		path = ft_strjoin(path_try[index], "/"); //add malloc protection later
		path = ft_strjoin(path, mini->cmds_link_test->cmds[0]); // leak here fix later
		if (!access(path, F_OK))
		{
			ft_free(path_try);
			return (path);
		}
		free(path);
		index++;
	}
	return (NULL);
}

void	generate_test_env(t_mini *mini)
{
	t_cmds	*cmds;
	t_cmds	*cmds_2;

	cmds = generate_cmds(mini, 0);
	cmds_2 = generate_cmds(mini, 1);
	add_node_cmds(&mini->cmds_link_test, cmds);
	add_node_cmds(&mini->cmds_link_test, cmds_2);
}

void	run_cmd(t_mini *mini)
{
	char	*path;
	int		index;
	char	*test;

	index = 0;
	path = find_path(mini);
	mini->cmds_link_test->cmds[0] = path; //leaks
	execve(path, mini->cmds_link_test->cmds, mini->env_copy);
	exit(0);
}

/*Will handle errors later prototype to see if the idea works*/
void	create_fork(t_mini *mini)
{
	pid_t	pid;
	t_cmds *head;
	int		ret;

	generate_test_env(mini);
	head = mini->cmds_link_test;
	pid = 0;
	while (mini->cmds_link_test)
	{
		pipe_redirection(mini);
		pid = fork();
		if (pid == 0)
			run_cmd(mini);
		mini->cmds_link_test = mini->cmds_link_test->next;
		pipe_restore(mini);
	}
	mini->cmds_link_test = head;
	close_pipes_subroutine(mini);
	if (pid > 0)
		waitpid(pid, NULL, 0);
}
