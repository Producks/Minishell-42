/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_definitons.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:45:11 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/14 16:56:28 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_DEFINITONS_H
# define COMMON_DEFINITONS_H

/* Define which os the user is running */

# ifdef __linux__
#  define OS 1
# endif

# ifdef __APPLE__
#  define OS 0
# endif

# ifndef OS
#  define OS 2
# endif

/* Common definitions */

# define SUCCESS 0
# define FAILURE -1

/* Status code definitions */

# define GENERAL_ERROR 1
# define COMMAND_LINE_ERROR 2
# define COMMAND_NOT_FOUND 127

/* Lexer, parsing and interpreter definitions */

# define SINGLE_QUOTE 39 
# define DOUBLE_QUOTE 34
# define DOLLAR_SIGN  36
# define QUESTION_MARK 63
# define UNDERSCORE 95

/* Redirection definitions */

# define REDIRECTION_PIPE 50
# define READ_INPUT 52 
# define READ_OUTPUT 51
# define APPEND_OUT 54
# define APPEND_IN 53

/* Builtins definitions */

# define BUILTIN_SUCCESS 0
# define BUILTIN_COMMAND_ERROR 1

/* Colors definitions */

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

#endif