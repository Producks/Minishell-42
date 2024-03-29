/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:43:28 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/12 16:06:14 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../interpreter.h"

int	replace_exit_status(t_dollar *expand)
{
	char	*exit_status;
	char	*trim_str;

	exit_status = ft_itoa(g_exit_status);
	if (!exit_status)
		return (print_errno(ENOMEM), FAILURE);
	trim_str = str_cutcut(expand->result, exit_status, "$?");
	if (!trim_str)
		return (free(exit_status), print_errno(ENOMEM), FAILURE);
	free(expand->result);
	free(exit_status);
	expand->result = trim_str;
	return (SUCCESS);
}

static int	dollar_dispatcher(t_dollar *expand, t_mini *mini)
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
				expand->ret = dollar_expandable(expand, mini);
			if (expand->ret == FAILURE)
				return (FAILURE);
		}
		if (!expand->result[expand->index])
			break ;
		expand->index++;
	}
	return (SUCCESS);
}

char	*dollar_interpreter(char *str, t_mini *mini)
{
	t_dollar	expand;

	expand.result = ft_strdup(str);
	if (!expand.result)
		return (print_errno(ENOMEM), NULL);
	if (dollar_dispatcher(&expand, mini) == FAILURE)
		return (NULL);
	return (expand.result);
}
