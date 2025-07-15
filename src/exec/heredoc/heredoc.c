/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:08:40 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/15 10:22:50 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

uint64_t	init_x_hdoc(t_x_hdoc *hdoc, char *limiter, char **env, t_ms *ms)
{
	hdoc->errors = 0;
	hdoc->env = env;
	hdoc->limiter = limiter;
	hdoc->qmark_value = ms->status;
	hdoc->to_expand = rm_quotes_limiter(hdoc->limiter);
	hdoc->pipes[0][0] = -1;
	hdoc->pipes[0][1] = -1;
	hdoc->pipes[1][0] = -1;
	hdoc->pipes[1][1] = -1;
	if (pipe(hdoc->pipes[0]) < 0 || (hdoc->to_expand
			&& pipe(hdoc->pipes[1]) < 0))
		ms->errors |= E_PIPE;
	hdoc->mlen_hdoc = 0;
	hdoc->act_len = -1;
	hdoc->vname = 0;
	hdoc->i_vname = 0;
	hdoc->c = '\n';
	hdoc->br = 0;
	hdoc->pname = ms->pname;
	return (hdoc->errors);
}

int	clean_heredoc(t_x_hdoc hdoc, t_ms *ms)
{
	free(hdoc.vname);
	close_fd(&(hdoc.pipes[0][PIPE_WRITE]));
	close_fd(&(hdoc.pipes[1][PIPE_READ]));
	close_fd(&(hdoc.pipes[1][PIPE_WRITE]));
	if (hdoc.errors || g_sig == SIGINT || ms->errors)
	{
		if (hdoc.errors & E_WRITE)
			ga_fprintf(2, "%s: heredoc: write error\n", ms->pname);
		if (g_sig == SIGINT)
		{
			hdoc.errors &= ~E_READ;
			write(2, "\n", 1);
		}
		close_fd(&(hdoc.pipes[0][PIPE_READ]));
	}
	return (hdoc.pipes[0][PIPE_READ]);
}

int	one_heredoc(char *delim, char **env, t_ms *ms)
{
	t_x_hdoc	hdoc;

	if (init_x_hdoc(&hdoc, delim, env, ms))
		return (clean_heredoc(hdoc, ms));
	read_stdin_no_exp(&hdoc, hdoc.pipes[hdoc.to_expand][PIPE_WRITE]);
	if (hdoc.errors)
		return (clean_heredoc(hdoc, ms));
	if (hdoc.to_expand)
	{
		close_fd(&hdoc.pipes[hdoc.to_expand][PIPE_WRITE]);
		hdoc.vname = malloc(sizeof(char) * hdoc.mlen_hdoc);
		if (hdoc.vname)
			hdoc_read_fd_exp(hdoc.pipes[1][PIPE_READ],
				hdoc.pipes[0][PIPE_WRITE], &hdoc);
		else
			ms->errors |= E_MLC;
	}
	return (clean_heredoc(hdoc, ms));
}

int	launch_heredocs(t_snippet *delims, char **env, t_ms *ms)
{
	uint64_t	errors;
	int			fd_hdoc;

	errors = 0;
	fd_hdoc = -1;
	if (!delims)
		return (-1);
	capture_signal_hdoc(SIG_HDOC_SET, ms);
	while (delims && !errors && !g_sig)
	{
		swap_fds(&fd_hdoc, one_heredoc(delims->ptr, env, ms));
		delims = delims->next;
	}
	capture_signal_hdoc(SIG_HDOC_RESET, ms);
	return (fd_hdoc);
}
