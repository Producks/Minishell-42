/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:20:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 16:50:08 by ddemers          ###   ########.fr       */
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

extern int	g_exit_status;

/* Read_input.c */

int	read_input(t_mini *mini);

/* Read_input_heredoc.c */

int	write_to_heredoc(t_mini *mini, int fd);

#endif