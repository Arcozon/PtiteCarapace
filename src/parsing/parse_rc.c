/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:31:37 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 18:31:53 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arcoms.h"
#include "get_next_line.h"

bool	exec_rc(char **str, t_ms *ms, int fd)
{
	t_snippet	*lst;

	lst = lexer(*str);
	free(*str);
	*str = 0;
	if (!lst)
		return (true);
	if (check_syntaxe(lst, MS_RC))
	{
		ms->msrc_fd = fd;
		optimize_lst(&lst);
		exec_start(ms, &lst);
		ms->msrc_fd = -1;
		return (true);
	}
	free_snip_lst(lst);
	return (false);
}

void	parse_rc_file(t_ms *ms, char *file)
{
	static int	l;
	char		*str;
	int			len;
	const int	fd = open(file, O_RDONLY);

	if (fd < 0)
		return ((void)ms_perror(ms->pname, file));
	str = get_next_line(fd);
	while (str && ++l)
	{
		if (is_statement_open(str) || *str == '#')
		{
			if (*str != '#')
				ga_fprintf(2, "%s: %s: line %i opened\n", ms->pname, file, l);
			(free(str), str = get_next_line(fd));
			continue ;
		}
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			str[len - 1] = 0;
		if (!exec_rc(&str, ms, fd))
			ga_fprintf(2, "%s: %s: line %i syntax error\n", ms->pname, file, l);
		(free(str), str = get_next_line(fd));
	}
	close(fd);
}
