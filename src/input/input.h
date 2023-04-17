/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:20:01 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 14:22:14 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdio.h>
# include "../../libs/readline/history.h"
# include "../../libs/readline/readline.h"
# include "../execution/execution.h"
# include "../lexer/lexer.h"
# include "../interpreter/interpreter.h"

extern int	g_exit_status;

/* Read_input.c */

int	read_input(t_mini *mini);

/* Read_input_heredoc.c */

int	write_to_heredoc(t_mini *mini, int fd);

#endif