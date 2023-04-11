/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expandable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:54:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/04/10 14:55:48 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../interpreter.h"

static size_t	get_length(t_expandable *expand)
{
	expand->index = 0;
	expand->length = 0;
	while (expand->str_literal[expand->index] != DOLLAR_SIGN)
			expand->index++;
	expand->dollar_index_start = expand->index;
	expand->index++;
	if (expand->str_literal[expand->index] == '{')
		expand->index++;
	if (!check_expandable(expand->str_literal[expand->index])) // refacto here later
		return (0);
	if (ft_isdigit(expand->str_literal[expand->index]))
		return (0);
	expand->index++;
	expand->length++;
	while (check_expandable(expand->str_literal[expand->index++]))
		expand->length++;
	return (0); // fix this shit later
}

static int	get_cut_str(t_expandable *expand)
{
	int	j;

	j = 0;
	expand->index = expand->dollar_index_start;
	expand->original_cut = malloc(sizeof(char) * (expand->length + 4));
	if (!expand->original_cut)
		return (print_errno(ENOMEM), FAILURE);
	expand->original_cut[j++] = expand->str_literal[expand->index++];
	if (expand->str_literal[expand->index] == '{')
		expand->original_cut[j++] = expand->str_literal[expand->index++];
	while (check_expandable(expand->str_literal[expand->index]))
		expand->original_cut[j++] = expand->str_literal[expand->index++];
	if (expand->str_literal[expand->index] == '}')
		expand->original_cut[j++] = expand->str_literal[expand->index++];
	expand->original_cut[j] = '\0';
	return (SUCCESS);
}

static int	get_env_str(t_expandable *expand)
{
	int		j;

	j = 0;
	expand->index = expand->dollar_index_start;
	expand->env_check = malloc(sizeof(char) * (expand->length + 1));
	if (!expand->env_check)
		return (print_errno(ENOMEM), FAILURE);
	expand->index++;
	if (expand->str_literal[expand->index] == '{')
		expand->index++;
	while (check_expandable(expand->str_literal[expand->index]))
		expand->env_check[j++] = expand->str_literal[expand->index++];
	expand->env_check[j] = '\0';
	return (SUCCESS);
}

static int	get_envp(t_mini *mini, t_expandable *expand)
{
	int	index;

	index = 0;
	while (mini->env_copy[index])
	{
		if (!ft_strncmp(expand->env_check,
				mini->env_copy[index], expand->length))
		{
			if (mini->env_copy[index][expand->length] == '=')
			{
				expand->env_str = ft_strdup(mini->env_copy[index]
						+ expand->length + 1);
				if (!expand->env_str)
					return (print_errno(ENOMEM), FAILURE);
				return (SUCCESS);
			}
			index++;
			continue ;
		}
		index++;
	}
	expand->env_str = ft_calloc(1, sizeof(char) * 1);
	if (!expand->env_str)
		return (print_errno(ENOMEM), FAILURE);
	return (SUCCESS);
}

int	dollar_expandable(t_dollar *dollar, t_mini *mini)
{
	t_expandable	expand;

	expand.str_literal = dollar->result;
	get_length(&expand);
	expand.ret = get_env_str(&expand);
	if (expand.ret == FAILURE)
		return (FAILURE);
	expand.ret = get_cut_str(&expand);
	if (expand.ret == FAILURE)
		return (free(expand.env_check), FAILURE);
	expand.ret = get_envp(mini, &expand);
	if (expand.ret == FAILURE)
		return (free(expand.env_check), free(expand.original_cut), FAILURE);
	expand.cut_result = str_cutcut(dollar->result,
			expand.env_str, expand.original_cut);
	if (!expand.cut_result)
		return (print_errno(ENOMEM), free(expand.env_check),
			free(expand.original_cut),
			free(expand.env_str), FAILURE);
	free(dollar->result);
	dollar->result = expand.cut_result;
	free (expand.env_str);
	free (expand.env_check);
	free (expand.original_cut);
	return (SUCCESS);
}
