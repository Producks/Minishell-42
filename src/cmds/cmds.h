/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cperron <cperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 14:16:15 by cperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "../utils/utils.h"

extern int	g_exit_status;

int		echo(char **message);
int		pwd(t_mini *mini);
int		env(char **env_copy);
int		cd(t_mini *mini);
int		ft_export(t_mini *mini);
int		ft_exit(t_mini *mini);
int		unset(t_mini *mini, int index, int j, bool error);

#endif