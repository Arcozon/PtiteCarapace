/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ppl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:44:45 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:30:09 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	pipe_ms(int pipes[2], t_ms *ms)
{
	if (pipe(pipes))
		ms->errors = E_PIPE;
	return (ms->errors);
}
uint64_t	launch_part_ppl(t_base *node, t_ms *ms, int p_in, int p_out)
{
	if (node->cmd.fd_in == -1)
		node->cmd.fd_in = p_in;
	node->cmd.fd_out = p_out;
	if (node->e_type == SUB)
		launch_subsh(node, ms);
	else if (node->e_type == CMD)
		exec_ppl_cmd(node, ms);
	close_fd(&node->cmd.fd_in);
	close_fd(&node->cmd.fd_out);
	return (ms->errors);
}

uint64_t	launch_ppl(t_base *node, t_ms *ms)
{
	int	pipes[2];
	int	last_pipe;

	last_pipe = -1;
	if (pipe_ms(pipes, ms))
		ms_exit(ms->errors, ms);
	while (node->e_type == PPL)
	{
		if (launch_part_ppl(node->left, ms, last_pipe, pipes[PIPE_WRITE]))
			ms_exit(ms->errors, ms);
		last_pipe = pipes[PIPE_READ];
		if (pipe_ms(pipes, ms))
			ms_exit(ms->errors, ms);
		node = node->right;
	}
	if (launch_part_ppl(node, ms, last_pipe, -1))
		ms_exit(ms->errors, ms);
	return (ms->errors);
}

void	wait_ppl(t_base *node, t_ms *ms)
{
	while (node->e_type == PPL)
	{
		waitpid(node->left->cmd.pid, &node->left->cmd.rstatus, 0);
		node = node->right;
	}
	waitpid(node->right->cmd.pid, &node->right->cmd.rstatus, 0);
	ms->status = node->right->cmd.rstatus & MASK_STATUS;
}

void	exec_ppl(t_base *node, t_ms *ms)
{
	launch_ppl(node, ms);
	wait_ppl(node, ms);
}
