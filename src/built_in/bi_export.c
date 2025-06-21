/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:56:02 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:54:14 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

#define E_NOSPACE 1
#define E_NOVALID 2
#define E_MLLCENV 3

static inline int	errors_export(char *pname, int error, char *identifier)
{
	size_t	id_len;

	if (error && pname)
	{
		write(2, pname, ft_strlen(pname));
		write(2, ": ", 2);
	}
	if (error == E_NOSPACE)
		write(2, "export: write error: No space left on device\n", 45);
	else if (error == E_NOVALID)
	{
		id_len = ft_strlen(identifier);
		write(2, "export: `", 9);
		write(2, identifier, id_len);
		write(2, "': not a valid identifier\n", 26);
	}
	else if (error == E_MLLCENV)
		write(2, "export: malloc error\n", 21);
	return (error != 0);
}

static inline int	check_identifier(char *arg)
{
	size_t	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (E_NOVALID);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && arg[i] != '_')
			return (E_NOVALID);
		++i;
	}
	return (NO_ERR);
}

int	bi_export(int ac, char **av, int fds[2], t_ms *ms)
{
	int	r_value;
	int	i;

	i = 1;
	while (i < ac)
	{
		if (check_identifier(av[i]) == E_NOVALID)
			r_value = errors_export(ms->pname, E_NOVALID, av[i]);
		else if (add_var_env(&ms->env, av[i]) == E_MLC)
			return (errors_export(ms->pname, E_MLLCENV, 0));
		++i;
	}
	return (r_value);
	(void)fds;
}
