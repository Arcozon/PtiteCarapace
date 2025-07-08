/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rcfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:00 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 19:31:51 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

bool	get_fd(int *fd)
{
	char	*tmp;

	tmp = ("HOME");
	if (!tmp)
		return (false);
	tmp = ft_strsjoin((char *[]){tmp, "/", MS_RC, NULL});
	if (!tmp)
		return (false);
	*fd = open(tmp, O_RDONLY);
	free(tmp);
	if (*fd < 0)
		return (false);
	return (true);
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

int	check_alias_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_strchr(FORBIDDEN_CHAR_ALIAS, str[i]))
			return (1);
		i++;
	}
	if (str[i] != '=')
		return (2);
	else if (is_statement_open(str + i + 1))
		return (3);
	return (0);
}
