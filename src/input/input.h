/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:20:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 14:04:11 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include "../utils/struct.h"
# include "../../libs/readline/history.h"
# include "../../libs/readline/readline.h"
# include "../../libs/Libft/libft.h"
# include "../execution/execution.h"
# include "../cmds/cmds.h"
# include "../lexer/lexer.h"
# include "../interpreter/interpreter.h"

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define PNK   "\x1B[38;5;206m"
# define RESET "\x1B[0m"
# define LRED  "\x1B[91m"
# define LGRN  "\x1B[92m"
# define LYEL  "\x1B[93m"
# define LBLU  "\x1B[94m"
# define LMAG  "\x1B[95m"
# define LCYN  "\x1B[96m"
# define LGRY  "\x1B[37;1m"
# define DGRY  "\x1B[90m"
# define BRED  "\x1B[38;2;255;0;0m"
# define BGRN  "\x1B[38;2;0;255;0m"
# define BBLU  "\x1B[38;2;0;0;255m"
# define ORNG  "\x1B[38;2;255;165;0m"
# define PURP  "\x1B[38;2;128;0;128m"
# define TEAL  "\x1B[38;2;0;128;128m"
# define DORNG "\x1B[38;2;255;140;0m"
# define BRWN  "\x1B[38;2;165;42;42m"

extern int	g_exit_status;

/* Read_input.c */

int	read_input(t_mini *mini);

/* Read_input_heredoc.c */

int	write_to_heredoc(t_mini *mini, int fd);

#endif