/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ge_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:10:00 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 12:42:37 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	cmd_dup(t_cmd *cmd)
{
	if (cmd->fd_in >= 0 && dup2(cmd->fd_in, STDIN_FILENO) < 0)
		cmd->errors |= E_DUP;
	if (cmd->fd_out >= 0 && dup2(cmd->fd_out, STDOUT_FILENO) < 0)
		cmd->errors |= E_DUP;
	close_fd(&cmd->fd_out);
	close_fd(&cmd->fd_in);
	return (cmd->errors);
}

uint64_t	cmd_open(int *oldfd, char *fname, int mode, char *pname)
{
	int	new_fd;

	new_fd = open(fname, mode, 0644);
	if (new_fd < 0)
	{
		ms_perror(pname, fname);
		return (E_OPEN);
	}
	swap_fds(oldfd, new_fd);
	return (NO_ERR);
}

void	cmd_waitpid(t_cmd *cmd)
{
	int	rstatus;

	rstatus = 0;
	while (waitpid(cmd->pid, &rstatus, 0) != cmd->pid)
		;
	if (WIFSIGNALED(rstatus))
		cmd->rstatus = WTERMSIG(rstatus) + STT_SIG_BASE;
	else
		cmd->rstatus = WEXITSTATUS(rstatus);
}

uint32_t	is_non_executable(char *path_exe)
{
	return (path_exe == PTR_CMD_NOT_FOUND
		|| path_exe == (char *)PTR_NO_SUCH_FILE);
}
