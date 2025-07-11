/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:04:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 12:55:52 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	execve_cmd(t_cmd *cmd, t_ms *ms)
{
	if (!cmd_dup(cmd))
	{
		if (cmd->builtin)
			cmd->rstatus = cmd->builtin(get_ac(cmd->argv_cmd),
					cmd->argv_cmd, (int [2]){0, 1}, ms);
		else
		{
			execve(cmd->path_exe, cmd->argv_cmd, ms->env.tab);
			cmd->rstatus = 126;
			if (!ft_is_file_lnk(cmd->path_exe))
				print_error_2(ms->pname, cmd->path_exe, "Is not a file");
			else
				ms_perror(ms->pname, cmd->path_exe);
		}
		ms_exit(cmd->rstatus, ms);
	}
	ms_exit(cmd->errors, ms);
	return (cmd->errors);
}

void	setup_ppl_cmd(t_cmd *cmd, t_ms *ms)
{
	if (!open_redir(cmd, ms) && !create_argv(cmd, ms))
	{
		ms->errors |= find_exe(&cmd->path_exe, &cmd->builtin, cmd->argv_cmd[0],
				find_content_var(PATH_VNAME, ms->env.tab));
		if (ms->errors)
			ms_exit(ms->errors, ms);
		if (cmd->argv_cmd[0])
		{
			if (!cmd->builtin && is_non_executable(cmd->path_exe))
			{
				cmd->rstatus = STT_CMD_NOT_FOUND;
				print_error_2(ms->pname, cmd->argv_cmd[0],
					(char *[]){ERR_CMD_NOT_FOUND,
					strerror(errno)}[(uintptr_t)cmd->path_exe]);
				ms_exit(cmd->rstatus, ms);
			}
			execve_cmd(cmd, ms);
		}
	}
	if (cmd->errors & E_OPEN)
		cmd->rstatus = 0;
	ms_exit(cmd->rstatus, ms);
}

void	exec_ppl_cmd(t_base *node, t_ms *ms, int to_close)
{
	ms->errors |= ms_fork(&node->cmd.pid, ms);
	if (ms->errors)
		ms_exit(ms->errors, ms);
	if (node->cmd.pid)
		return ;
	close_fd(&to_close);
	setup_ppl_cmd(&node->cmd, ms);
}
