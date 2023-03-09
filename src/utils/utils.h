/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:07:10 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/09 13:53:56 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../main/struct.h"

t_cmds *create_node_cmds(void);
void	add_node_cmds(t_cmds **head, t_cmds *new_node);
void	delete_node_cmds(t_cmds **head, t_cmds *node_to_delete);
void	*free_linked_list_mini(t_cmds **head);

#endif