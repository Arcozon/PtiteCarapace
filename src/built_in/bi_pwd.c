/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:11:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/24 13:02:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	bi_pwd(int ac, char **av, int fds[2], t_ms *ms)
{
	ssize_t	len;
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (ms_perror(ms->pname, "pwd"), 1);
	len = ge_strlen(cwd);
	if (write(fds[PIPE_WRITE], cwd, len) != len
		|| write(fds[PIPE_WRITE], "\n", 1) != 1)
	{
		free(cwd);
		ms_perror(ms->pname, "pwd");
		return (1);
	}
	free(cwd);
	return (0);
	(void)ac, (void)av;
}
