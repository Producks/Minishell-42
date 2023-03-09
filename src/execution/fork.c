/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/08 17:32:51 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmds	*generate_cmds(int flag)
{
	t_cmds *cmds;

	cmds = create_node_cmds();
	if (flag == 0)
	{
		cmds->cmds = ft_split("echo weee", ' ');
		cmds->fd_in = 0;
		cmds->fd_out = 1;
	}
	else
	{
		cmds->cmds = ft_split("cat", ' ');
		cmds->fd_in = 1;
		cmds->fd_out = 0;
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

/*typedef struct s_cmds
{
	char			**cmds;
	char			*path;
	int				in;
	int				out;
	char			*infile;
	char			*outfile;
	struct s_cmds	*previous;
	struct s_cmds	*next;
}	t_cmds;*/
int	pipe_deez(t_cmds *prev_cmd, t_cmds *curr_cmd, int fd[2])
{
    if (curr_cmd->fd_in == 1)
    {
        dup2(fd[READ_PIPE], STDIN_FILENO);
      	close(fd[WRITE_PIPE]);
    }
    else if (curr_cmd->fd_out == 1)
    {
        dup2(fd[WRITE_PIPE], STDOUT_FILENO);
     	close(fd[READ_PIPE]);
    }
    return (0);
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
		pipe_restore(mini, 0, 1);
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
}


// ret = pipe_deez(mini->cmds_link_test->previous, mini->cmds_link_test, fd);


// void	make_child(int nbr, char *message, char *envp[])
// {
// 	int id;

// 	id = fork();
// 	if (id == 0)
// 	{
// 		char *test[] = {"/bin/bash", "-c", message, NULL};
// 		execve("/bin/bash", test, envp);
// 	}
// 	wait(&id);
// }

// void	create_child(char *message, char *envp[])
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		exit (0);
// 	if (pid == 0)
// 	{
// 		char *test[] = {"/bin/bash", "-c", message, NULL};
// 		execve("/bin/bash", test, envp);
// 	}
// 	else
// 		wait(&pid);
// }