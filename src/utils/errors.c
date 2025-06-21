/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:03:15 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 12:18:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	ms_perror(char *pname, char *context)
{
	write(2, pname, ft_strlen(pname));
	write(2, ": ", 2);
	perror(context);
}

void	print_error(char *pname, char *error_msg)
{
	write(2, pname, ft_strlen(pname));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}

void	print_code_error(uint64_t errors, char *pname)
{
	if (errors & E_DUP)
		print_error(pname, "Dup error");
	if (errors & E_MLC)
		print_error(pname, "Malloc error");
	if (errors & E_FORK)
		print_error(pname, "Malloc error");
}

void	ms_exit(int rstatus, t_ms *ms)
{
	print_code_error(ms->errors, ms->pname);
	free_ms(ms);
	exit(rstatus);
}
