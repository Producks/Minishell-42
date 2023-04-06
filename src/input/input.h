/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:20:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/05 21:42:10 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
//#include <readline/readline.h> // fix later
//#include <readline/history.h> // fix later
# include "../utils/struct.h"
# include "../../libs/readline/history.h"
# include "../../libs/readline/readline.h"
# include "../../libs/Libft/libft.h"
# include "../execution/execution.h"
# include "../cmds/cmds.h"
# include "../lexer/lexer.h"
# include "../interpreter/interpreter.h"

extern int	g_exit_status;

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define PNK   "\x1B[38;5;206m"
# define RESET "\x1B[0m"

extern int	g_exit_status;

/* Read_input.c */

int	read_input(t_mini *mini);

#endif