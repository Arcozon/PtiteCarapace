/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_noexp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:31:27 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 19:59:21 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	heredoc_handle_dollar(char c, int *mlv);

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
		heredoc_handle_dollar()
		if (!hdoc->limiter[i_l] && *c == '\n')
			return (0);
		if (*c != hdoc->limiter[i_l])
			break ;
		++i_l;
	}
	if (write(fd, hdoc->limiter, i_l) != i_l)
		hdoc->errors |= E_WRITE;
	return (1);
}

// act_len is the len of the var name we are in
void	heredoc_handle_dollar(char c, int *mlv)
{
	static int	act_len = -1;
	int			out;

	out = 0;
	if (c == '$' && act_len == -1)
		act_len = 0;
	else if (act_len != -1)
	{
		if (act_len == 0 && (c >= '0' && c <= '9'))
			out = (++act_len, 1);
		else if (is_var_name(c))
			++act_len;
		else
			out = 1;
	}
	if (out)
	{
		if (*mlv < act_len)
			*mlv = act_len;
		act_len = -1;
	}
}

int	read_stdin(t_x_hdoc *hdoc, int fdin)
{
	char	c;
	int		br;

	c = '\n';
	br = 1;
	while (1)
	{
		if (br < 0)
			return (-1);
		if (c == '\n')
		{
			write(2, "> ", 2);
			br = read_start_line(fdin, hdoc, &c, &br);
			if (br <= 0)
				return (br);
		}
		else
			br = read(STDIN_FILENO, &c, 1);
		if (br == 1)
			(write(fdin, &c, 1), heredoc_handle_dollar(c, &(hdoc->mlen_hdoc)));
	}
	return (0);
}
