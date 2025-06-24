/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ppl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:44:45 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/24 14:58:09 by gaeudes          ###   ########.fr       */
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
	swap_fds(&node->cmd.fd_in, p_in);
	swap_fds(&node->cmd.fd_out, p_out);
	// if (node->cmd.fd_in == -1)
	// 	node->cmd.fd_in = p_in;
	// if (node->cmd.fd_out == -1)
	// 	node->cmd.fd_out = p_out;
	DEBUG("NPIN: %d", node->cmd.fd_in)
	DEBUG("NPOUT: %d", node->cmd.fd_out)
	if (node->e_type == SUB)
		launch_subsh(node, ms);
	else if (node->e_type == CMD)
		exec_ppl_cmd(node, ms);
	close_fd(&node->cmd.fd_in);
	close_fd(&node->cmd.fd_out);
	return (ms->errors);
}

void	ppl_exit(int last_pipe, int pipes[2], uint8_t status, t_ms *ms)
{
	close_fd(&last_pipe);
	close_fd(&pipes[PIPE_READ]);
	close_fd(&pipes[PIPE_WRITE]);
	ms_exit(status, ms);
}

uint64_t	launch_ppl(t_base *node, t_ms *ms)
{
	int	pipes[2];
	int	last_pipe;

	pipes[0] = -1;
	pipes[1] = -1;
	last_pipe = -1;
	while (node->e_type == PPL)
	{
		if (pipe_ms(pipes, ms))
			ppl_exit(last_pipe , pipes, ms->errors, ms);
		if (launch_part_ppl(node->left, ms, last_pipe, pipes[PIPE_WRITE]))
			ppl_exit(last_pipe , pipes, ms->errors, ms);
		last_pipe = pipes[PIPE_READ];
		node = node->right;
	}
	if (launch_part_ppl(node, ms, last_pipe, -1))
		ppl_exit(last_pipe , pipes, ms->errors, ms);
	return (ms->errors);
}

void	wait_ppl(t_base *node, t_ms *ms)
{
	while (node->e_type == PPL)
	{
		waitpid(node->left->cmd.pid, &node->left->cmd.rstatus, 0);
		node = node->right;
	}
	waitpid(node->cmd.pid, &node->cmd.rstatus, 0);
	ms->status = node->cmd.rstatus & MASK_STATUS;
}

void	exec_ppl(t_base *node, t_ms *ms)
{
	launch_ppl(node, ms);
	wait_ppl(node, ms);
}
