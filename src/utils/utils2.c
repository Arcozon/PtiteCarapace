/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:01:24 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:08:28 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	print_until(char *str, char c, int fd)
{
	int	i;

	i = 0;
	if (!str || !*str || fd < 0)
		return ;
	while (str[i] && str[i] != c)
		i++;
	write(fd, str, i);
}

char	*_basename(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (str);
	while (str[i])
		i++;
	i--;
	while (str[i] != '/' && i > 0)
		i--;
	return (str + i + (str[i] == '/'));
}

char	*pass_whitespace(char *str)
{
	if (!str)
		return (NULL);
	while (is_white_space(*str))
		str++;
	return (str);
}

