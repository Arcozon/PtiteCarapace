/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:09:21 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/23 17:48:07 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	exec_node(t_base *node, t_ms *ms)
{
	static void	(*exec_fct[])(t_base*, t_ms*) = {exec_scol, exec_and,
		exec_or, exec_ppl, exec_simple_cmd, exec_subsh};

	exec_fct[node->e_type](node, ms);
	ms->status = node->cmd.rstatus & MASK_STATUS;
}

void	exec_heredoc(t_base *node, t_ms *ms)
{
	if (!node)
		return ;
	if (node->cmd.heredoc)
		node->cmd.fd_in = launch_heredocs(node->cmd.heredoc, ms->env.tab, ms);
	exec_heredoc(node->left, ms);
	exec_heredoc(node->right, ms);
}

void	exec_start(t_ms *ms)
{
	if (g_sig)
	{
		ms->status = g_sig + 0x80;
		g_sig = 0;
	}
	//Make BTREE
	set_sig(EXEC, ms);
	exec_heredoc(ms->exec_tree, ms);
	exec_node(ms->exec_tree, ms);
	free_node(&ms->exec_tree);
	g_sig = 0;
	set_sig(ROUTINE, ms);
}
