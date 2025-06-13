/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:56:02 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/13 17:44:20 by gaeudes          ###   ########.fr       */
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
		write(2, "export: '", 9);
		write(2, identifier, id_len);
		write(2, "': not a valid identifier\n", 26);
	}
	else if (error == E_MLLCENV)
		write(2, "export: malloc error\n", 21);
	return (error != 0);
}

static inline int	print_export(t_env *env, int fds[2])
{
	uint64_t	i;
	int			len;
	int			len_content;

	i = 0;
	//sort env by ascii
	while (env->env[i])
	{
		len = 0;
		while (env->env[i][len] && env->env[i][len] != '=')
			++len;
		len_content = ft_strlen(env->env[i] + len);
		if (7 != write(fds[PIPE_WRITE], "export ", 7)
				|| len != write(fds[PIPE_WRITE], env->env[i], len)
				|| 1 != write(fds[PIPE_WRITE], "\"", 1)
				|| len_content != write(fds[PIPE_WRITE], env->env[i] + len,
				len_content) || 2 != write(fds[PIPE_WRITE], "\"\n", 2))
			return (E_NOSPACE);
		++i;
	}
	return (EXIT_SUCCESS);
}

static inline int	check_identifier(char *arg)
{
	size_t	i;

	if (!ft_isalpha(arg[0]) || arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isdigit(arg[i]) || !ft_isalpha(arg[i]) || arg[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

int	bi_export(int ac, char **av, t_env *env, int fds[2], char *pname)
{
	int		r_value;
	size_t	i;

	r_value = 0;
	if (ac <= 1)
		return (errors_export(pname, print_export(env, fds), 0));
	else
	{
		i = 1;
		while (av[i])
		{
			if (!check_identifier(av[i]))
				r_value = errors_export(pname, E_NOVALID, av[i]);
			else if (add_var_env(env, av[i]) == E_MLC)
				return (errors_export(pname, E_MLLCENV, 0));
			++i;
		}
	}
	return (r_value);
}
