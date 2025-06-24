/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:08:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 18:02:10 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	write_qmark_value(int fdout, uint8_t qmark_value)
{
	int	error;

	error = 0;
	if (qmark_value / 100)
		error += (write(fdout, &"0123456789"[(qmark_value / 100)], 1) != 1);
	if (qmark_value / 10)
		error += (write(fdout, &"0123456789"[(qmark_value / 10 % 10)], 1) != 1);
	error += (write(fdout, &"0123456789"[(qmark_value % 10)], 1) != 1);
	if (error)
		return (E_WRITE);
	return (0);
}

uint64_t	write_var_content(int fdout, t_x_hdoc *hdoc)
{
	uint64_t	i;

	i = 0;
	if (!hdoc->i_vname)
	{
		if (write(fdout, "$", 1) != 1)
			return (E_WRITE);
		return (0);
	}
	if (hdoc->vname[0] == '?')
		return (write_qmark_value(fdout, hdoc->qmark_value));
	while (hdoc->env[i])
	{
		if (ft_strncmp_weq(hdoc->vname, hdoc->env[i], hdoc->i_vname) == 0)
			break ;
		++i;
	}
	if (hdoc->env[i] && write(fdout, hdoc->env[i] + hdoc->i_vname + 1,
			ft_strlen(hdoc->env[i] + hdoc->i_vname + 1))
		!= (ssize_t)ft_strlen(hdoc->env[i] + hdoc->i_vname + 1))
		return (E_WRITE);
	return (0);
}

void	read_var_name(int fdin, int fdout, t_x_hdoc *hdoc)
{
	hdoc->i_vname = 0;
	while (1)
	{
		hdoc->br = read(fdin, &hdoc->c, 1);
		if (hdoc->br <= 0)
			break ;
		if (hdoc->i_vname == 0 && !(ft_isalpha(hdoc->c)
				|| hdoc->c == '_' || hdoc->c == '?'))
			break ;
		else if (hdoc->i_vname >= 1 && !(ft_isalpha(hdoc->c)
				|| hdoc->c == '_' || ft_isdigit(hdoc->c)))
			break ;
		hdoc->vname[hdoc->i_vname] = hdoc->c;
		++hdoc->i_vname;
		if (hdoc->i_vname == 1 && hdoc->c == '?')
		{
			hdoc->br = read(fdin, &hdoc->c, 1);
			break ;
		}
	}
	if (hdoc->br >= 0)
		hdoc->errors |= write_var_content(fdout, hdoc);
}

int	hdoc_read_fd_exp(int fdin, int fdout, t_x_hdoc *hdoc)
{
	hdoc->br = read(fdin, &hdoc->c, 1);
	while (hdoc->br == 1 && !hdoc->errors)
	{
		if (hdoc->c == '$')
		{
			read_var_name(fdin, fdout, hdoc);
			continue ;
		}
		if (hdoc->c != '$' && hdoc->br == 1 && write(fdout, &hdoc->c, 1) != 1)
			return (hdoc->errors |= E_WRITE, -1);
		hdoc->br = read(fdin, &hdoc->c, 1);
	}
	if (hdoc->br < 0)
		hdoc->errors |= E_READ;
	return (0);
}
