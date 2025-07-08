/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ge_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:31:24 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 17:32:23 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	ge_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*ge_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		++str;
	}
	if (c == 0)
		return (str);
	return (0);
}

uint32_t	findslash(const char *str)
{
	uint32_t	last_slash;
	uint32_t	i;

	i = 0;
	last_slash = -1;
	while (str[i])
	{
		if (str[i] == '/')
			last_slash = i;
		++i;
	}
	return (last_slash + 1);
}
