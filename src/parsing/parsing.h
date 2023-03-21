/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:56:15 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/17 23:09:47 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stdio.h>
#include <string.h>
//#include <readline/readline.h> // fix later
//#include <readline/history.h> // fix later
# include "../main/struct.h"
# include "../../libs/readline/history.h"
# include "../../libs/readline/readline.h"
# include "../../libs/Libft/libft.h"
# include "../execution/execution.h"
# include "../cmds/cmds.h"

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

int check_input(t_mini *mini);
int	read_input(t_mini *mini);
int tokenize(t_mini *mini);

void	redir_list(char **tokens);
void	*free_linked_list_redirr(t_redir **head);
void	parse_linked_list(char **tokens, int num_token);

#endif