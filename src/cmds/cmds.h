/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:15:29 by ddemers           #+#    #+#             */
/*   Updated: 2023/02/28 13:36:23 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

int		echo(char **message);
int		pwd(void);
int		env(char *envp[]);
int		cd(char *message);
int		export(void);
int		ft_exit(void);
int		unset(void);

#endif