/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:47:59 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/17 23:39:44 by cperron          ###   ########.fr       */
/*   Updated: 2023/03/19 00:00:38 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../lexer/lexer.h"
#include "../utils/utils.h"

void	print_token(char **tokens, int num_tokens)
{
	int i;

	i = 0;
	while (i < num_tokens)
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

int tokenize(t_mini *mini)
{
	int 	num_tokens;
	char *str;
    char delim[3];
    char *token;
	char **tokens;
	char message[] = "echo < 'hello' | echo > echo >> prt << urt";

	usleep(50000);
	delim[0] = ' ';
	delim[1] = '\'';
	delim[2] = '"';
	num_tokens = 0;
	tokens = ft_calloc(sizeof(char*), 100);
	str = ft_calloc(sizeof(char), ft_strlen(message) + 1);
	str = strcpy(str, message);
    token = strtok(str, delim);
	free(str);
    while (token != NULL)
	{
		usleep(50000);
        // printf("%s\n", token);
		tokens[num_tokens] = token;
        token = strtok(NULL, delim);
		num_tokens++;
    }
	token = NULL;
	num_tokens++;
	tokens[num_tokens] = token;
	
	// printf("%s\n", token);
	printf("number of token: %d\n", num_tokens);
	// print_token(tokens, num_tokens);
	parse_linked_list(tokens, num_tokens);
	free(tokens);
	return (0);
}

int	check_if_utils(t_mini *mini)
{
	if (ft_strcmp(mini->cmd[0], "echo") == 0)
		echo(mini->cmd); 
	else if (ft_strcmp(mini->cmd[0], "cd") == 0)
		cd(mini);
	else if (ft_strcmp(mini->cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(mini->cmd[0], "export") == 0)
		ft_export(mini);
	else if (ft_strcmp(mini->cmd[0], "unset") == 0)
		unset(mini);
	else if (ft_strcmp(mini->cmd[0], "env") == 0)
		env(mini->env_copy);
	else if (ft_strcmp(mini->cmd[0], "exit") == 0)
		ft_exit(mini);
	else if (ft_strcmp(mini->cmd[0], "debug") == 0) // special variable to test pipes
		lexer(mini);
	else if (ft_strcmp(mini->cmd[0], "chris") == 0)
		tokenize(mini);
	else if (ft_strcmp(mini->cmd[0], "gpt") == 0)
		system("open https://chat.openai.com");
	return (1);
}

int check_input(t_mini *mini)
{
	mini->cmd = ft_split(mini->message, ' ');
	if (check_if_utils(mini) == 0)
		ft_free(mini->cmd);
	mini->cmd = ft_free(mini->cmd);
	return (1);
}
