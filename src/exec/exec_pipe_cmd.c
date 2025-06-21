/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:04:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:27:29 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	execve_cmd(t_cmd *cmd, t_ms *ms)
{

	if (!cmd_dup(cmd))
	{
		if (cmd->builtin)
		{
			cmd->rstatus = cmd->builtin(get_ac(cmd->argv_cmd), cmd->argv_cmd, (int[2]){0,1}, ms);
			ms_exit(cmd->rstatus, ms);
		}
		else
		{
			execve(cmd->path_exe, cmd->argv_cmd, ms->env.tab);
			cmd->rstatus = 126;
			ms_perror(ms->pname, cmd->path_exe);
		}
		close(0);
		close(1);
	}
	return (cmd->errors);
}

void	setup_ppl_cmd(t_cmd *cmd, t_ms *ms)
{
	if (!open_redir(cmd, ms->pname) && !create_argv(cmd, ms))
	{
		ms->errors |= find_exe(&cmd->path_exe, &cmd->builtin, cmd->argv_cmd[0],
			find_path(ms->env.tab));
		if (ms->errors)
			ms_exit(ms->errors, ms);
		if (cmd->argv_cmd[0])
		{
			if (!cmd->path_exe && !cmd->builtin)
			{
				cmd->rstatus = 127;
				ms_perror(ms->pname, cmd->path_exe);
				ms_exit(cmd->rstatus, ms);
			}
			if (execve_cmd(cmd, ms))
				print_code_error(cmd->errors, ms->pname);
		}
	}
	if (cmd->errors & E_OPEN && !cmd->argv_cmd[0])
		cmd->rstatus = 0;
	ms_exit(cmd->rstatus, ms);
}

void	exec_ppl_cmd(t_base *node, t_ms *ms)
{
	ms->errors |= ms_fork(&node->cmd.pid, ms);
	if (ms->errors)
		ms_exit(ms->errors, ms);
	if (node->cmd.pid)
		return ;
	setup_ppl_cmd(&node->cmd, ms);
}
