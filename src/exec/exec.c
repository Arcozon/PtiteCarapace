/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:09:21 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:24:05 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	exec_simple_cmd(t_base *node, t_ms *ms);

void	exec_scol(t_base *node, t_ms *ms)
{
	if (!node->left)
		WAIT
	if (!ms->errors)
		exec_node(node->left, ms);
	if (!ms->errors && node->right)
		exec_node(node->right, ms);
}

void	exec_and(t_base *node, t_ms *ms)
{
	if (!ms->errors && node->left)
		exec_node(node->left, ms);
	if (!ms->errors && node->right  && ms->status == 0)
		exec_node(node->right, ms);
}

void	exec_or(t_base *node, t_ms *ms)
{
	if (!node->left && !node->right)
		WAIT
	if (!ms->errors)
		exec_node(node->left, ms);
	if (!ms->errors && ms->status != 0)
		exec_node(node->right, ms);
}

void	launch_subsh(t_base *node, t_ms *ms)
{
	if (ms_fork(&(node->cmd.pid), ms))
		ms_exit(ms->errors, ms);
	if (!node->cmd.pid)
	{
		if (open_redir(&node->cmd, ms->pname))
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

void	exec_node(t_base *node, t_ms *ms)
{
	static void	(*exec_fct[])(t_base*, t_ms*) = {exec_scol, exec_and,
		exec_or, exec_ppl, exec_simple_cmd, exec_subsh};

	exec_fct[node->e_type](node, ms);
	ms->status = node->cmd.rstatus & MASK_STATUS;
}
