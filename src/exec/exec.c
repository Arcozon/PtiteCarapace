/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:09:21 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/24 20:01:18 by gaeudes          ###   ########.fr       */
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

void	kill_all(t_base *node)
{
	if (!node)
		return ;
	// WAIT
	kill_all(node->left);
	kill_all(node->right);
	if (node->cmd.pid != -1)
	{
		WAIT
		kill(node->cmd.pid, SIGINT);
	}
}

void	exec_start(t_ms *ms, t_snippet **lexer)
{
	if (g_sig)
	{
		ms->status = g_sig + STT_SIG_BASE;
		g_sig = 0;
	}
	if (make_base(lexer, &ms->exec_tree))
		WAIT
	set_sig(EXEC, ms);
	exec_heredoc(ms->exec_tree, ms);
	if (g_sig)
	{
		ms->status = g_sig + STT_SIG_BASE;
		g_sig = 0;
		return ;
	}
	exec_node(ms->exec_tree, ms);
	kill_all(ms->exec_tree);
	free_node(&ms->exec_tree);
	if (g_sig)
	{
		ms->status = g_sig + STT_SIG_BASE;
		g_sig = 0;
	}
	set_sig(ROUTINE, ms);
}
