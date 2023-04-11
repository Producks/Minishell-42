/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:07:10 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/11 14:37:49 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"
# include "../errors/error.h"

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define SUCCESS 0
# define FAILURE -1
# define UNDERSCORE 95

# ifdef __linux__
#  define OS 1
# endif

# ifdef __APPLE__
#  define OS 0
# endif

# ifndef OS
#  define OS 2
# endif

t_cmds	*create_node_cmds(void);
void	add_node_cmds(t_cmds **head, t_cmds *new_node);
void	*free_linked_list_mini(t_cmds **head);

void	clean_redir_list(t_cmds *current);

/* print_startup.c*/

void	print_startup(void);

/* Init.c */

int		init_struct_mini(t_mini *mini, char *envp[]);
void	free_struct_mini(t_mini *mini);

/* Signal.c */

void	init_child_signal(void);
void	init_parent_signals(void);
void	child_signal_handler(int signal);
void	parent_signal_handler(int signal);

/* Create_file_name.c */

void	create_file_name(char *str, int number);

/* Env_functions.c */

int		add_env_element(t_mini *mini, char *str_to_add);
int		copy_env(t_mini *mini, char *envp[]);

/* Str_cutcut.c */

char	*str_cutcut(char *original, char *replacement, char *to_replace);

/* Strjoin_path.c */

char	*strjoin_path(char const *s1, char const *s2, char sep);

/* Check_expandable.c */

bool	check_expandable(char c);

#endif