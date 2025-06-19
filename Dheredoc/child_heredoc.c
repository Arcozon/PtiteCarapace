/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:08:40 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/19 12:40:47 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	init_x_hdoc(t_x_hdoc *hdoc, char **env, char *pname)
{
	hdoc->errors = 0;
	hdoc->env = env;
	hdoc->pipes[0][0] = -1;
	hdoc->pipes[0][1] = -1;
	hdoc->pipes[1][0] = -1;
	hdoc->pipes[1][1] = -1;
	hdoc->hdoc_fd = -1;
	hdoc->pid = -1;
	hdoc->mlen_hdoc = 0;
	hdoc->act_len = -1;
	hdoc->vname = 0;
	hdoc->i_vname = 0;
	hdoc->c = '\n';
	hdoc->br = 0;
	hdoc->pname = pname;
	hdoc->qmark_value = 0;
}

int	rm_quotes_limiter(char *limiter)
{
	int		need_exp;
	char	quote;
	int		i;
	int		d_cpy;

	need_exp = 1;
	i = 0;
	d_cpy = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '"')
		{
			need_exp = (++d_cpy, 0);
			quote = limiter[i];
			while (limiter[++i] && limiter[i] != quote)
				limiter[i - d_cpy] = limiter[i];
			++d_cpy;
		}
		else
			limiter[i - d_cpy] = limiter[i];
		++i;
	}
	limiter[i - d_cpy] = 0;
	return (need_exp);
}

void	quit_heredoc(uint64_t errors, t_x_hdoc hdoc, t_ms minishell)
{
	free(hdoc.vname);
	close_fd(&(hdoc.pipes[0][0]));
	close_fd(&(hdoc.pipes[0][1]));
	close_fd(&(hdoc.pipes[1][0]));
	close_fd(&(hdoc.pipes[1][1]));
	(void)minishell;
	exit(errors);
}

void	child_hdoc(t_x_hdoc hdoc, t_ms minishell)
{
	close_fd(&hdoc.pipes[0][PIPE_READ]);
	hdoc.to_expand = rm_quotes_limiter(hdoc.limiter);
	if (hdoc.to_expand && pipe(hdoc.pipes[1]) < 0)
		quit_heredoc(hdoc.errors | E_PIPE, hdoc, minishell);
	read_stdin_no_exp(&hdoc, hdoc.pipes[hdoc.to_expand][PIPE_WRITE]);
	if (hdoc.to_expand)
	{
		close_fd(&hdoc.pipes[hdoc.to_expand][PIPE_WRITE]);
		hdoc.vname = malloc(hdoc.mlen_hdoc);
		if (hdoc.vname)
			read_fd_exp(hdoc.pipes[1][PIPE_READ], hdoc.pipes[0][PIPE_WRITE], &hdoc);
		else
			hdoc.errors |= E_MLC;
	}
	quit_heredoc(hdoc.errors, hdoc, minishell);
}

int	launch_heredocs(t_snippet *delims, char **env, t_ms minishell, char *pname)
{
	t_x_hdoc	hdoc;
	int			r_value;	(void)minishell;

	init_x_hdoc(&hdoc, env, pname);
	while (delims && !hdoc.errors)
	{
		hdoc.limiter = delims->ptr;
		if(pipe(hdoc.pipes[0]) < 0)
			hdoc.errors |= E_PIPE;
		if (!hdoc.errors)
		{
			hdoc.pid = fork();
			if (hdoc.pid == -1)
				hdoc.errors |= E_FORK;
			else if (!hdoc.pid)
				child_hdoc(hdoc, minishell);
			else
			{
				close(hdoc.pipes[0][PIPE_WRITE]);
				waitpid(hdoc.pid, &r_value, 0);
			}
		}
		delims = delims->next;
	}
	return (hdoc.pipes[0][PIPE_READ]);
}

