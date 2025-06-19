/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:08:40 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/19 16:44:47 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

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

uint64_t	init_x_hdoc(t_x_hdoc *hdoc, char *limiter, char **env, t_ms minishell)
{
	hdoc->errors = 0;
	hdoc->env = env;
	hdoc->limiter = limiter;
	hdoc->qmark_value = 0; //take from minishell
	hdoc->to_expand = rm_quotes_limiter(hdoc->limiter);
	hdoc->pipes[0][0] = -1;
	hdoc->pipes[0][1] = -1;
	hdoc->pipes[1][0] = -1;
	hdoc->pipes[1][1] = -1;
	if (pipe(hdoc->pipes[0]) < 0 || (hdoc->to_expand && pipe(hdoc->pipes[1]) < 0))
		hdoc->errors |= E_PIPE;
	hdoc->mlen_hdoc = 0;
	hdoc->act_len = -1;
	hdoc->vname = 0;
	hdoc->i_vname = 0;
	hdoc->c = '\n';
	hdoc->br = 0;
	hdoc->pname = minishell;
	return (hdoc->errors);
}

int	clean_heredoc(t_x_hdoc hdoc, t_ms minishell)
{
	free(hdoc.vname);
	close_fd(&(hdoc.pipes[0][PIPE_WRITE]));
	close_fd(&(hdoc.pipes[1][PIPE_READ]));
	close_fd(&(hdoc.pipes[1][PIPE_WRITE]));
	if (hdoc.errors)
	{
		(void)minishell; // add errors to minishell
		close_fd(&(hdoc.pipes[0][PIPE_READ]));
		return (-1);
	}
	return (hdoc.pipes[0][PIPE_READ]);
}

int	one_heredoc(char *delim, char **env, t_ms minishell)
{
	t_x_hdoc	hdoc;

	if (init_x_hdoc(&hdoc, delim, env, minishell))
		return (clean_heredoc(hdoc, minishell));
	hdoc.errors |= read_stdin_no_exp(&hdoc, hdoc.pipes[hdoc.to_expand][PIPE_WRITE]);
	if (hdoc.to_expand)
	{
		close_fd(&hdoc.pipes[hdoc.to_expand][PIPE_WRITE]);
		hdoc.vname = malloc(sizeof(char) * hdoc.mlen_hdoc);
		if (hdoc.vname)
			read_fd_exp(hdoc.pipes[1][PIPE_READ], hdoc.pipes[0][PIPE_WRITE], &hdoc);
		else
			hdoc.errors |= E_MLC;
	}
	return (clean_heredoc(hdoc, minishell));
}

int	launch_heredocs(t_snippet *delims, char **env, t_ms minishell)
{
	uint64_t	errors = 0;
	int			fd_hdoc;

	fd_hdoc = -1;
	capture_signal(0);
	while (delims && !errors && !g_sig)
	{
		swap_fds(&fd_hdoc, one_heredoc(delims->ptr, env, minishell));
		delims = delims->next;
	}
	capture_signal(1);
	if (g_sig)	
		swap_fds(&fd_hdoc, -1);
	g_sig = 0;
	return (fd_hdoc);
}

