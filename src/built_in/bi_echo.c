/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:40:54 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/24 14:04:43 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

#define ECHO_WRITE_ERR 1

int	write_echo(char *str, int fd_out, char *pname)
{
	ssize_t	len;

	len = ge_strlen(str);
	if (write(fd_out, str, len) != len)
	{
		print_error(pname, "echo: write error: No space left on device");
		return (ECHO_WRITE_ERR);
	}
	return (0);
}

char	**skip_dash_n(char **av, int *dash_n)
{
	int	i;

	*dash_n = 0;
	while (*av && av[0][0] == '-' && av[0][1])
	{
		i = 1;
		while (av[0][i] == 'n')
			++i;
		if (av[0][i])
			break ;
		*dash_n = 1;
		++av;
	}
	return (av);
}

int	bi_echo(int ac, char **av, int fds[2], t_ms *ms)
{
	int	dash_n;

	av = skip_dash_n(++av, &dash_n);
	while (*av)
	{
		if (write_echo(*av, fds[PIPE_WRITE], ms->pname) == ECHO_WRITE_ERR)
			return (ECHO_WRITE_ERR);
		++av;
		if (*av
			&& write_echo(" ", fds[PIPE_WRITE], ms->pname) == ECHO_WRITE_ERR)
			return (ECHO_WRITE_ERR);
	}
	if (!dash_n
		&& write_echo("\n", fds[PIPE_WRITE], ms->pname) == ECHO_WRITE_ERR)
		return (ECHO_WRITE_ERR);
	return (0);
	(void)ac;
}
