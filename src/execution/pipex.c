/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/07 13:01:04 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> //linux only for wait and waitpid
#include <sys/wait.h> //linux only for wait and waitpid
#include "../../libs/Libft/libft.h"
#include "../main/struct.h"
#include "../utils/utils.h"

void	make_child(int nbr, char *message, char *envp[])
{
	int id;

	id = fork();
	if (id == 0)
	{
		char *test[] = {"/bin/bash", "-c", message, NULL};
		execve("/bin/bash", test, envp);
	}
	wait(&id);
}

void	create_child(char *message, char *envp[])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit (0);
	if (pid == 0)
	{
		char *test[] = {"/bin/bash", "-c", message, NULL};
		execve("/bin/bash", test, envp);
	}
	else
		wait(&pid);
}

t_cmds	*generate_cmds(int flag)
{
	t_cmds *cmds;

	cmds = create_node_cmds();
	if (flag == 0)
	{
		cmds->cmds = ft_split("ls", ' ');
		cmds->in = 0;
		cmds->out = 1;
	}
	else
	{
		cmds->cmds = ft_split("ls", ' ');
		cmds->in = 1;
		cmds->out = 0;
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

	cmds = generate_cmds(0);
	cmds_2 = generate_cmds(1);
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

void	create_fork(t_mini *mini)
{
	pid_t	pid;
	t_cmds *head;
	int		pipe[2];

	generate_test_env(mini);
	head = mini->cmds_link_test;
	pid = 0;
	while (mini->cmds_link_test)
	{
		pid = fork();
		//dup2();
		//close();
		if (pid == 0)
			run_cmd(mini);
		mini->cmds_link_test = mini->cmds_link_test->next;
	}
	waitpid(pid, NULL, 0);
	return ;
}
