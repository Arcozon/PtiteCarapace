/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_opp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:33:25 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/24 13:27:36 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	exec_scol(t_base *node, t_ms *ms)
{
	if (!ms->errors)
		exec_node(node->left, ms);
	if (!ms->errors && node->right && g_sig != SIGINT)
		exec_node(node->right, ms);
}

void	exec_and(t_base *node, t_ms *ms)
{
	if (!ms->errors && node->left)
		exec_node(node->left, ms);
	if (!ms->errors && node->right && ms->status == 0 && g_sig != SIGINT)
		exec_node(node->right, ms);
}

void	exec_or(t_base *node, t_ms *ms)
{
	if (!ms->errors)
		exec_node(node->left, ms);
	if (!ms->errors && ms->status != 0 && g_sig != SIGINT)
		exec_node(node->right, ms);
}

void	launch_subsh(t_base *node, t_ms *ms)
{
	if (ms_fork(&(node->cmd.pid), ms))
		ms_exit(ms->errors, ms);
	if (!node->cmd.pid)
	{
		if (open_redir(&node->cmd, ms))
			ms_exit(node->cmd.rstatus, ms);
		if (cmd_dup(&node->cmd))
			ms_exit(E_DUP, ms);
		exec_node(node->left, ms);
		ms_exit(ms->status, ms);
	}
}

void	exec_subsh(t_base *node, t_ms *ms)
{
	launch_subsh(node, ms);
	waitpid(node->cmd.pid, &node->cmd.rstatus, 0);
}
