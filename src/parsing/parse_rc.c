/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:31:37 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/04 11:08:12 by gaeudes          ###   ########.fr       */
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

void	exec_rc(char *str, t_ms *ms)
{
	t_snippet	*lst;

	lst = lexer(str);
	if (check_syntaxe(lst, MS_RC))
	{
		replace_tilde(lst, expand(ms->env.tab, "HOME", 4));
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
