/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_changed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 00:10:56 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/17 00:11:26 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

char	*get_dir_changed(t_mini *mini, int count)
{
	char	*current;
	char	*ret;
	size_t	len;

	current = ft_strdup(mini->current_dir);
	if (!current)
		return (print_errno(errno), NULL);
	len = ft_strlen(current);
	while (len != 0)
	{
		if (current[len] == '/')
			count--;
		if (count == 0)
		{
			ret = ft_substr(current, 0, len);
			if (!ret)
				return (free(current), print_errno(errno), NULL);
			return (free(current), ret);
		}
		len--;
	}
	return (free(current), NULL);
}
