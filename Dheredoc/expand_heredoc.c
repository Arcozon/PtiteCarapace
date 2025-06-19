/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:08:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/19 12:26:49 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	write_var_content(int fdout, t_x_hdoc *hdoc)
{
	uint64_t	i;

	i = 0;
	if (!hdoc->i_vname)
	{
		write(fdout, "$", 1);
		return ;
	}
	if (hdoc->vname[0] == '?')
	{
		if (hdoc->qmark_value / 100)
			write(fdout, &"0123456789"[(hdoc->qmark_value / 100)], 1);
		if (hdoc->qmark_value / 10)
			write(fdout, &"0123456789"[(hdoc->qmark_value / 10) % 10], 1);
		write(fdout, &"0123456789"[hdoc->qmark_value % 10], 1);
	}
	while (hdoc->env[i])
	{
		if (ft_strncmp_weq(hdoc->vname, hdoc->env[i], hdoc->i_vname) == 0)
			break ;
		++i;
	}
	if (hdoc->env[i])
		write(fdout, hdoc->env[i] + hdoc->i_vname+ 1,
			ft_strlen(hdoc->env[i] + hdoc->i_vname+ 1));
}

// Shitty implementation by me makes it so i need to have it recursive
// (Once i read the char that not in the var_name i might need to call 
// read var name again if its a $, otherwise its lost before the check for $
// in the read_fd_exp fct)  -- shoudl implement like the len calc in no_exp.c
void	read_var_name(int fdin, int fdout, t_x_hdoc *hdoc)
{
	hdoc->i_vname = 0;
	while (1)
	{
		hdoc->br = read(fdin, &hdoc->c, 1);
		if (hdoc->br <= 0)
			break ;
		if (hdoc->i_vname == 0 && !(ft_isalpha(hdoc->c) || hdoc->c == '_' || hdoc->c == '?'))
			break;
		else if (hdoc->i_vname >= 1 && !(ft_isalpha(hdoc->c) || hdoc->c == '_' || ft_isdigit(hdoc->c)))
			break;
		hdoc->vname[hdoc->i_vname] = hdoc->c;
		++hdoc->i_vname;
		if (hdoc->i_vname == 1 && hdoc->c == '?')
		{
			hdoc->br = read(fdin, &hdoc->c, 1);
			break ;
		}
	}
	if (hdoc->br >= 0)
		write_var_content(fdout, hdoc);
}

int	read_fd_exp(int fdin, int fdout, t_x_hdoc *hdoc)
{
	hdoc->br = read(fdin, &hdoc->c, 1);
	while (hdoc->br == 1)
	{
		if (hdoc->c == '$')
		{
			read_var_name(fdin, fdout, hdoc);
			continue ;
		}
		if (hdoc->c != '$' && hdoc->br == 1)
			write(fdout, &hdoc->c, 1);
		hdoc->br = read(fdin, &hdoc->c, 1);
	}
	if (hdoc->br < 0)
		hdoc->errors |= E_READ;
	return (0);
}
