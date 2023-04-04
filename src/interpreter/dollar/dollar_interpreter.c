/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:43:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/04 16:36:39 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../interpreter.h"

int	replace_exit_status(t_expandable *expand)
{
	char	*exit_status;
	char	*trim_str;

	exit_status = ft_itoa(g_exit_status);
	if (!exit_status)
		return (print_errno(ENOMEM), FAILURE);
	trim_str = str_cutcut(expand->result, exit_status, "$?");
	if (!trim_str) // check if I need to free later str incase of failure
		return (free(exit_status), print_errno(ENOMEM), FAILURE);
	free(expand->result);
	free(exit_status);
	expand->result = trim_str;
	return (SUCCESS);
}

static int	dollar_dispatcher(t_expandable *expand)
{
	expand->index = 0;
	expand->ret = 0;
	while (expand->result[expand->index])
	{
		if (expand->result[expand->index] == DOLLAR_SIGN)
		{
			if (expand->result[expand->index + 1] == QUESTION_MARK)
				expand->ret = replace_exit_status(expand);
			else
				expand->ret = dollar_expandable(expand);
			if (expand->ret == FAILURE)
				return (FAILURE);
		}
		if (!expand->result[expand->index])
		{
			puts("fix"); // should fix more testing later
			break ;
		}
		expand->index++;
	}
	return (SUCCESS);
}

char	*dollar_interpreter(char *str)
{
	t_expandable	expand;

	expand.result = ft_strdup(str);
	if (!expand.result)
		return (print_errno(ENOMEM), NULL);
	if (dollar_dispatcher(&expand) == FAILURE)
		return (print_errno(ENOMEM), NULL);
	return (expand.result);
}
