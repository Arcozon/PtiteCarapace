/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:31:37 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/09 16:42:39 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arcoms.h"
#include "get_next_line.h"

void	exec_rc(char *str, t_ms *ms)
{
	t_snippet	*lst;

	lst = lexer(str);
	if (check_syntaxe(lst, MS_RC))
	{
		optimize_lst(&lst);
		exec_start(ms, &lst);
	}
	else
		free_snip_lst(lst);
}

void	parse_rc_file(t_ms *ms, char *filename)
{
	int			line;
	char		*str;
	int			len;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	str = get_next_line(fd);
	line = 0;
	while (str && ++line)
	{
		if (is_statement_open(str) || *str == '#')
		{
			(free(str), str = get_next_line(fd));
			continue ;
		}
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			str[len - 1] = 0;
		exec_rc(str, ms);
		(free(str), str = get_next_line(fd));
	}
	close(fd);
}
