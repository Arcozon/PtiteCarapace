/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ppl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:44:45 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 13:05:43 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	launch_part_ppl(t_base *node, t_ms *ms, int p_in, int pipes[2])
{
	handle_submslvl(&ms->env);
	swap_fds(&node->cmd.fd_in, p_in);
	swap_fds(&node->cmd.fd_out, pipes[PIPE_WRITE]);
	if (node->e_type == SUB)
		launch_subsh(node, ms, pipes[PIPE_READ]);
	else if (node->e_type == CMD)
		exec_ppl_cmd(node, ms, pipes[PIPE_READ]);
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
			ppl_exit(last_pipe, pipes, ms->errors, ms);
		if (launch_part_ppl(node->left, ms, last_pipe, pipes))
			ppl_exit(last_pipe, pipes, ms->errors, ms);
		last_pipe = pipes[PIPE_READ];
		node = node->right;
	}
	if (launch_part_ppl(node, ms, last_pipe, (int []){-1, -1}))
		ppl_exit(last_pipe, pipes, ms->errors, ms);
	return (ms->errors);
}

uint8_t	wait_ppl(t_base *node)
{
	while (node->e_type == PPL)
	{
		cmd_waitpid(&node->left->cmd);
		node = node->right;
	}
	cmd_waitpid(&node->cmd);
	return (node->cmd.rstatus);
}

void	exec_ppl(t_base *node, t_ms *ms)
{
	launch_ppl(node, ms);
	node->cmd.rstatus = wait_ppl(node);
}
