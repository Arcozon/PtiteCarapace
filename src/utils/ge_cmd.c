/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ge_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:10:00 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 18:10:02 by malfwa           ###   ########.fr       */
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
	cmd->rstatus = WEXITSTATUS(rstatus);
}
