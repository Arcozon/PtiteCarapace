/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rcfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:00 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 16:44:19 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

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
