/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 07:54:51 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/05 21:29:46 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

char	*strjoin_path(char const *s1, char const *s2, char sep)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!result)
		return (NULL);
	while (s1[++i])
		result[i] = s1[i];
	result[i++] = sep;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
