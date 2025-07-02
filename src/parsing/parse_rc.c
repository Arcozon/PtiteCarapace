/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:31:37 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/02 19:28:03 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arcoms.h"
#include "get_next_line.h"

void	parse_rc(t_ms *ms)
{
	char	*str;
	int		len;
	int		fd;

	if (!get_fd(&fd))
		return ;
	str = get_next_line(fd);
	while (str)
	{
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			str[len - 1] = 0;
		alias(&ms->table, str);
		free(str);
		str = get_next_line(fd);
	}
}
