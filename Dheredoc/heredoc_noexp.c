/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_noexp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:31:27 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/19 10:48:57 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	expected_limiter(t_x_hdoc *hdoc)
{
	write(2, "\n", 1);
	write(2, hdoc->pname, ft_strlen(hdoc->pname));
	write(2, ": warning: here-document delimited by end-of-file (wanted `", 59);
	write(2, hdoc->limiter, ft_strlen(hdoc->limiter));
	write(2, "')\n", 3);
}

// neg error, pos success, 0 not found
int	read_start_line(int fd, t_x_hdoc *hdoc, char *c, int *br)
{
	size_t	i_l;

	i_l = 0;
	while (1)
	{
		*br = read(STDIN_FILENO, c, 1);
		if (*br < 0)
			return (hdoc->errors |= E_READ, -1);
		if (!*br && i_l == 0)
			return (expected_limiter(hdoc), 0);
		else if (!*br)
			continue ;
		heredoc_handle_dollar(*c, hdoc);
		if (!hdoc->limiter[i_l] && *c == '\n')
			return (0);
		if (*c != hdoc->limiter[i_l])
			break ;
		++i_l;
	}
	if (write(fd, hdoc->limiter, i_l) != (ssize_t)i_l)
		hdoc->errors |= E_WRITE;
	return (1);
}

// act_len is the len of the var name we are in
void	heredoc_handle_dollar(char c, t_x_hdoc *hdoc)
{
	if (c == '$')
		hdoc->act_len = 0;
	else if (hdoc->act_len != -1)
	{
		if (hdoc->act_len == 0 && (ft_isalpha(c) || c == '_' || c == '?'))
			++hdoc->act_len;
		else if ((ft_isalpha(c) || c == '_' || ft_isdigit(c)))
			++hdoc->act_len;
		else
			hdoc->act_len = -1;
		if ((int)hdoc->mlen_hdoc < hdoc->act_len)
		{
			hdoc->mlen_hdoc = hdoc->act_len;
			DEBUG("New:[%lu]", hdoc->mlen_hdoc)
		}
		if (hdoc->act_len == 1 && c == '?')
		{
			if (hdoc->mlen_hdoc < 1)
				hdoc->mlen_env = 1;
			hdoc->act_len = -1;
		}
	}

}

int	read_stdin_no_exp(t_x_hdoc *hdoc, int fdin)
{
	while (1)
	{
		if (hdoc->br < 0)
			return (hdoc->errors |= E_READ, -1);
		if (hdoc->c == '\n')
		{
			write(2, "> ", 2);
			hdoc->br = read_start_line(fdin, hdoc, &hdoc->c, &hdoc->br);
			if (hdoc->br < 0)
				return (hdoc->errors |= E_READ, -1);
			if (!hdoc->br)
				return (0);
		}
		else
			hdoc->br = read(STDIN_FILENO, &hdoc->c, 1);
		if (hdoc->br == 1)
		{
			if (write(fdin,  &hdoc->c, 1) != 1)
				return (hdoc->errors |= E_WRITE, -1);
			heredoc_handle_dollar(hdoc->c, hdoc);
		}
	}
	return (0);
}
