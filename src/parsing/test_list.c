/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:07:13 by cperron           #+#    #+#             */
/*   Updated: 2023/04/14 17:26:08 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_more_redir(t_redir *current, int i)
{
	printf(GRN "node :%d\n" RESET, i);
	printf("add : %p\n", current);
	printf("in :%d\n", current->in);
	printf("out :%d\n", current->out);
	printf("filename : %s\n\n", current->filename);
	printf("next : %p\n", current->next);
}

void	print_redir_list(t_redir *redir)
{
	t_redir	*current;
	int		i;

	i = 1;
	current = redir;
	while (current)
	{
		if (current->type == 50)
			printf("|\n");
		if (current->type == 51)
			printf(">\n");
		if (current->type == 52)
			printf("<\n");
		if (current->type == 53)
			printf(">>\n");
		if (current->type == 54)
			printf("<<\n");
		print_more_redir(current, i);
		current = current->next;
		i++;
	}
}

void	printall(t_cmds *cmds)
{
	t_cmds	*current;
	int		i;

	i = 0;
	current = cmds;
	while (current)
	{
		i = 0;
		printf(YEL "cmds : %s\n" RESET, current->cmds[i]);
		i++;
		while (current->cmds[i])
		{
			printf(" arg :%s\n", current->cmds[i]);
			i++;
		}
		printf(" larg : %s\n", current->cmds[i]);
		printf(" redir : %p\n", current->redir_list);
		print_redir_list(current->redir_list);
		current = current->next;
		i++;
	}
}

void	print_token(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}
