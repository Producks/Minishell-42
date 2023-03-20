/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:07:10 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/19 17:34:29 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../main/struct.h"

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

typedef struct s_split
{
	int		nbr_elements;
	char	**array;
}	t_split;

t_cmds *create_node_cmds(void);
void	add_node_cmds(t_cmds **head, t_cmds *new_node);
void	delete_node_cmds(t_cmds **head, t_cmds *node_to_delete);
void	*free_linked_list_mini(t_cmds **head);
char	*strjoin_path(char const *s1, char const *s2, char sep);

/*Place holder for t_redir*/
void	*free_linked_list_redir(t_redir **head);
void	delete_node_redir(t_redir **head, t_redir *node_to_delete);
void	add_node_redir(t_redir **head, t_redir *new_node);
t_redir *create_node_redir(void);

/*Split*/
char	**ft_split(char const *s, char c);
void	test_function(t_mini *mini);

char	*str_cutcut(char *original, char *replacement, char *to_replace);

#endif


// static char	**get_size(char const *s, char c, t_split *a)
// {
// 	a->word_count = 1;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 			a->word_count++;
// 		if (*s == 39 || *s == '\"')
// 		{
// 			a->c = *s++;
// 			while (*s != a->c && *s != '\0')
// 				s++;
// 			if (*s == '\0')
// 				return (NULL);
// 			if (*s == a->c || *s == '\0')
// 				s++;
// 		}
// 		while (*s && *s != c)
// 			s++;
// 	}
// 	a->str = (char **)malloc(sizeof(char *) * a->word_count);
// 	if (!a->str)
// 		return (NULL);
// 	a->str[a->word_count - 1] = NULL;
// 	return (a->str);
// }