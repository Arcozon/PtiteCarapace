/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:34:45 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	dollar_n_sep(char c)
{
	if (ft_strchr(SEP, c) || c == '$')
		return (true);
	return (false);
}

bool	dollar_sep_quote(char c)
{
	if (ft_strchr(SEP, c) || c == '$' || c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	simple_sep(char c)
{
	if (ft_strchr(SEP, c))
		return (true);
	return (false);
}

bool	is_statement_open(char *str)
{
	char	quote;
	int		bracket;

	quote = 0;
	bracket = 0;
	if (!str)
		return (false);
	while (*str)
	{
		if ((quote == '\'' && *str == '\'') || (quote == '\"' && *str == '\"'))
			quote = '\0';
		else if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (!quote)
		{
			if (*str == '(' || *str == ')')
				bracket += (int []){-1, 1}[*str == '('];
		}
		str++;
	}
	return (quote || bracket > 0);
}
