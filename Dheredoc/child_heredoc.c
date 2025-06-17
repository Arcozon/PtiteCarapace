/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:08:40 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 19:44:47 by gaeudes          ###   ########.fr       */
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
	return (limiter[i - d_cpy] = 0, need_exp);
}

void	child_hdoc(t_x_hdoc hdoc, t_ms minishell)
{
	close(hdoc.pipes[0][PIPE_READ]);
	hdoc.to_expand = rm_quotes_limiter(hdoc.limiter);
	if (hdoc.to_expand && pipe(hdoc.pipes[1]))
		hdoc.errors |= E_PIPE;
	
	
}

uint64_t	get_mlen_env(char **env)
{
	size_t	len;
	size_t	m_len;

	m_len = 0;
	while (*env)
	{
		len = 0;
		while ((*env)[len] && (*env)[len] != '=')
			++len;
		if (m_len < len)
			m_len = len;
		++env;
	}
	return (m_len);
}

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
	hdoc->mlen_env = get_mlen_env(env);
	hdoc->mlen_hdoc = 0;
	hdoc->mlen_var = 0;
	hdoc->vname = 0;
	hdoc->i_name = 0;
	hdoc->pname = pname;
}

int	lauch_childs(t_snippet *delims, char **env, t_ms minishell, char *pname)
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
}


