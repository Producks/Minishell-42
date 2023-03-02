/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/02 12:28:58 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "../main/struct.h"

int		echo(char **message);
int		pwd(void);
int		env(char **env_copy);
int		cd(char *message);
int		ft_export(t_mini *mini);
void	ft_exit(t_mini *mini);
int		unset(t_mini *mini);

#endif