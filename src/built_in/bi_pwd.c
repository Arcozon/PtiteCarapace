/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:11:07 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/20 13:42:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(int ac, char **av, int fds[2], t_ms *ms)
{
	const char	*pwd_env = find_content_var(PWD_VNAME, ms->env.tab);
	ssize_t		len;
	char		*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		cwd = (char *)pwd_env;
	if (!cwd)
		return (ms_perror(ms->pname, "pwd"), 1);
	len = ge_strlen(cwd);
	if (write(fds[PIPE_WRITE], cwd, len) != len
		|| write(fds[PIPE_WRITE], "\n", 1) != 1)
	{
		if (cwd != pwd_env)
			free(cwd);
		ms_perror(ms->pname, "pwd");
		return (1);
	}
	if (cwd != pwd_env)
		free(cwd);
	return (0);
	(void)ac, (void)av;
}
