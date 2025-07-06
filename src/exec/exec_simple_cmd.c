/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:27:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/06 12:38:05 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	exec_simple_builtin(t_cmd *cmd, t_ms *ms)
{
	int	fds[2];

	fds[0] = 0;
	if (cmd->fd_in >= 0)
		fds[0] = cmd->fd_in;
	fds[1] = 1;
	if (cmd->fd_out >= 0)
		fds[1] = cmd->fd_out;
	cmd->rstatus = cmd->builtin(get_ac(cmd->argv_cmd), cmd->argv_cmd, fds, ms);
}

void	exec_simple_cmd_fork(t_cmd *cmd, t_ms *ms)
{
	ms->errors |= ms_fork(&cmd->pid, ms);
	if (ms->errors)
		ms_exit(ms->errors, ms);
	if (!cmd->pid)
	{
		ms->errors |= find_exe(&cmd->path_exe, &cmd->builtin,
				cmd->argv_cmd[0], find_content_var("PATH", ms->env.tab));
		if (ms->errors)
			ms_exit(ms->errors, ms);
		if (!cmd->path_exe && cmd->argv_cmd[0])
		{
			print_error_1(cmd->argv_cmd[0], ERR_CMD_NOT_FOUND);
			ms_exit(STT_CMD_NOT_FOUND, ms);
		}
		if (!cmd->argv_cmd[0])
			ms_exit(cmd->rstatus, ms);
		execve_cmd(cmd, ms);
	}
	else
		cmd_waitpid(cmd);
}

void	exec_simple_cmd(t_base *node, t_ms *ms)
{
	if (!open_redir(&node->cmd, ms) && !create_argv(&node->cmd, ms))
	{
		node->cmd.builtin = is_a_builtin(node->cmd.argv_cmd[0]);
		if (node->cmd.builtin)
			exec_simple_builtin(&node->cmd, ms);
		else
			exec_simple_cmd_fork(&node->cmd, ms);
	}
}
