/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_missing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:59:34 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:43:03 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wm_handle_quotes(int *missing, char *str, int *i)
{
	char	to_match;

	to_match = '"';
	if (*missing == m_squote)
		to_match = '\'';
	while (str[*i] && str[*i] != to_match)
		++*i;
	if (str[*i])
	{
		*missing = -1;
		++*i;
	}
}

int	sub_what_missing(int *missing, int *i, char *str, int *par_depth)
{
	if (!ft_strncmp(&str[*i], "&&", 2))
	{
		*missing = m_and;
		return (++*i, 1);
	}	
	else if (!ft_strncmp(&str[*i], "||", 2))
	{
		*missing = (++*i, m_or);
		return (1);
	}	
	else if (str[*i] == '|')
	{
		*missing = m_pipe;
		return (1);
	}	
	else if (str[*i] == '(' || str[*i] == ')')
	{
		*missing = -1;
		*par_depth += "\xff\1"[str[*i] == '('];
	}
	else if (!ge_isspace(str[*i]))
		return (*missing = -1, 1);
	return (0);
}

int	what_missing(char *str)
{
	static int	par_depth;
	static int	missing = -1;
	int			i;

	i = 0;
	while (str[i])
	{
		if (missing == m_squote || missing == m_dquote)
		{
			wm_handle_quotes(&missing, str, &i);
			continue ;
		}
		else if (sub_what_missing(&missing, &i, str, &par_depth))
			;
		if (str[i] == '\'' || str[i] == '"')
			missing = (int []){m_dquote, m_squote}[str[i] == '\''];
		++i;
	}
	if (missing == -1 && par_depth > 0)
		missing = m_par;
	return (missing);
}
