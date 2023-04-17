/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:07:10 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 00:14:09 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common_definitons.h"
# include "struct.h"
# include "../../libs/Libft/libft.h"
# include "../errors/error.h"

/* print_startup.c*/

void	print_startup(void);

/* Mini_struct_functions.c */

int		init_struct_mini(t_mini *mini, char *envp[]);
void	free_struct_mini(t_mini *mini);
void	clean_redir_list(t_cmds *current);
void	*free_linked_list_mini(t_cmds **head);

/* Signal.c */

void	signals_handler_parent(bool mute, bool is_interactive);
void	signals_handler_child(bool is_heredoc);
void	regular_shell(int signal);
void	interactive_shell(int signal);
void	heredoc_signal(int signal);

/* Create_file_name.c */

void	create_file_name(char *str, int number);

/* Env_functions.c */

int		add_env_element(t_mini *mini, char *str_to_add);
int		copy_env(t_mini *mini, char *envp[]);
int		add_pwd_to_env(t_mini *mini, char *old_pwd, int index, int count);

/* Str_cutcut.c */

char	*str_cutcut(char *original, char *replacement, char *to_replace);

/* Strjoin_path.c */

char	*strjoin_path(char const *s1, char const *s2, char sep);

/* Check_expandable.c */

bool	check_expandable(char c);

/* Free_linked_list_exec */

void	free_linked_list_execve(t_mini *mini);

/* Calculate_exit_status.c */

int		calculate_exit_status(int exit_status);

/* count_double_dot.c */

int		count_double_dot(const char *str);

/* get_dir_changed.c */

char	*get_dir_changed(t_mini *mini, int count);

#endif