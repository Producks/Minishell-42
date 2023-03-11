/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:56:15 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/11 07:53:03 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stdio.h>
//#include <readline/readline.h> // fix later
//#include <readline/history.h> // fix later
# include "../main/struct.h"
# include "../../libs/readline/history.h"
# include "../../libs/readline/readline.h"
# include "../../libs/Libft/libft.h"
# include "../execution/exec.h"
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

#endif