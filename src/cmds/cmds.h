/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/16 20:14:44 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../utils/struct.h"
# include "../../libs/Libft/libft.h"
# include "../errors/error.h"
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