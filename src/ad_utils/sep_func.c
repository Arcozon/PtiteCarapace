/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:34:45 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/04 12:21:03 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
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
