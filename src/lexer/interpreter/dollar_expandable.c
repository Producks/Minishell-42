/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expandable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemers <ddemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:54:14 by ddemers           #+#    #+#             */
/*   Updated: 2023/03/23 17:18:56 by ddemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static bool	check_expandable(char c)
{
	if ((ft_isalpha(c) || ft_isdigit(c) || c == UNDERSCORE))
		return (true);
	return (false);
}

static void	single_quote_inc(t_expandable *expand)
{
	expand->index++;
	while (expand->str_literal[expand->index] != SINGLE_QUOTE)
		expand->index++;
	expand->index++;
}

static size_t	get_length(t_expandable *expand)
{
	expand->index = 0;
	expand->length = 0;
	while (expand->str_literal[expand->index] != DOLLAR_SIGN)
	{
		if (expand->str_literal[expand->index] == SINGLE_QUOTE)
			single_quote_inc(expand);
		else
			expand->index++;
	}
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
}

static int	get_cut_str(t_expandable *expand)
{
	int	j;

	j = 0;
	expand->index = expand->dollar_index_start;
	expand->original_cut = malloc(sizeof(char) * (expand->length + 4));
	if (!expand->original_cut)
		return (FAILURE);
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
		return (FAILURE);
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
		if (!ft_strncmp(expand->env_check, mini->env_copy[index], expand->length))
			{
				if (mini->env_copy[index][expand->length] == '=')
				{
					expand->env_str = ft_strdup(mini->env_copy[index] + expand->length + 1);
					if (!expand->env_str)
						return (FAILURE);
					return (SUCCESS);
				}
				index++;
				continue ;
			}
		index++;
	}
	expand->env_str = malloc(sizeof(char) * 1);
	if (!expand->env_str)
		return (FAILURE);
	expand->env_str[0] = '\0';
	return (SUCCESS);
}

int	dollar_expandable(t_mini *mini, char **literal, int index) // check free order later
{
	t_expandable	expand;

	expand.str_literal = literal[index];
	get_length(&expand);
	expand.ret = get_env_str(&expand);
	if (expand.ret == FAILURE)
		return (FAILURE);
	expand.ret = get_cut_str(&expand);
	if (expand.ret == FAILURE)
		return (free(expand.env_str), FAILURE);
	expand.ret = get_envp(mini, &expand);
	if (expand.ret == FAILURE)
		return (free(expand.env_str), free(expand.original_cut), FAILURE);
	expand.cut_result = str_cutcut(literal[index], expand.env_str, expand.original_cut);
	if (!expand.cut_result)
		return (free(expand.env_str), free(expand.original_cut), free(expand.env_str), FAILURE);
	free(literal[index]);
	literal[index] = expand.cut_result;
	free (expand.env_str);
	free (expand.env_check);
	free (expand.original_cut);
	return (SUCCESS);
}
