/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_null_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:30:16 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 19:38:58 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	found_null(t_dstr out)
{
	size_t	i;

	i = 0;
	if (!out.str)
		return (0);
	while (i < out.size)
	{
		if (out.str[i] == '\0')
			return (1);
		++i;
	}
	return (0);
}

char	*clean_return(t_dstr *out, char *buff)
{
	free(buff);
	free(out->str);
	out->str = 0;
	out->size = 0;
	return (0);
}

void	empty_gnl(int fd)
{
	void	*ptr;

	if (fd < 0)
		return ;
	ptr = get_next_line(fd);
	while (ptr)
	{
		free(ptr);
		ptr = get_next_line(fd);
	}
}
