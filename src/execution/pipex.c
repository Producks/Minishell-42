/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/06 16:43:11 by ddemers          ###   ########.fr       */
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
		cmds->cmds = ft_split("echo hello", ' ');
		cmds->in = 0;
		cmds->out = 1;
	}
	else
	{
		cmds->cmds = ft_split("cat", ' ');
		cmds->in = 1;
		cmds->out = 0;
	}
	return (cmds);
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
	printf("%s\n", mini->cmds_link_test->cmds[0]);
	exit(0);
}

void	create_fork(t_mini *mini)
{
	pid_t	pid;
	t_cmds *head;

	generate_test_env(mini);
	head = mini->cmds_link_test;
	while (mini->cmds_link_test)
	{
		pid = fork();
		if (pid)
			run_cmd(mini);
		mini->cmds_link_test = mini->cmds_link_test->next;
	}
	waitpid(pid, NULL, 0);
	return ;
}
