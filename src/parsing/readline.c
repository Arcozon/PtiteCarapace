/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:08 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

int	get_cmd_line_fd(int	*fd, t_ms *ms)
{
	int		pipe_fds[2];
	int		status;
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		return (ms->errors |= E_PIPE, 1);
	pid = fork();
	if (pid < 0)
		return (close(pipe_fds[0]), close(pipe_fds[1]),
			ms->errors |= E_FORK, 1);
	if (!pid)
		arco_rdl_child(pipe_fds, ms);
	close(pipe_fds[1]);
	status = 0;
	while (waitpid(pid, &status, 0) != pid)
		;
	*fd = pipe_fds[0];
	return (get_exit_value(status));
}
