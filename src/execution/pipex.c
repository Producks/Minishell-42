/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 03:35:26 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/05 09:35:39 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../libs/Libft/libft.h"

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
