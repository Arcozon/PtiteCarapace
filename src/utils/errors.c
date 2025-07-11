/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:03:15 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 13:29:39 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	ms_c_perror(char *pname, char *err_msg, char *context)
{
	ga_fprintf(STDERR_FILENO, "%s: %s: %s: %s\n",
		pname, err_msg, context, strerror(errno));
}

void	ms_perror(char *pname, char *context)
{
	ga_fprintf(STDERR_FILENO, "%s: %s: %s\n", pname, context, strerror(errno));
}

void	print_error_1(char *pname, char *error_msg)
{
	ga_fprintf(STDERR_FILENO, "%s: %s\n", pname, error_msg);
}

void	print_error_2(char *pname, char *fname, char *error_msg)
{
	ga_fprintf(STDERR_FILENO, "%s: %s: %s\n", pname, fname, error_msg);
}

void	print_code_error(uint64_t errors, char *pname)
{
	if (errors & E_DUP)
		print_error_1(pname, "Dup error");
	if (errors & E_MLC)
		print_error_1(pname, "Malloc error");
	if (errors & E_FORK)
		print_error_1(pname, "Fork error");
}

void	ms_exit(int rstatus, t_ms *ms)
{
	print_code_error(ms->errors, ms->pname);
	free_ms(ms);
	exit(rstatus);
}
