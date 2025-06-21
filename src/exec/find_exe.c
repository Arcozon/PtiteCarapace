/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:31:40 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

char	*find_path(char **env)
{
	while (*env)
	{
		if (!ft_strncmp_weq("PATH", *env, 4))
			return (*env);
		++env;
	}
	return (0);
}

uint64_t	find_exe_int_path(char **ptr_exe, char *av0, char *path)
{
	uint64_t	start;
	uint64_t	len;

	start = 0;
	while (path[start])
	{
		len = 0;
		while (path[start + len] && path[start + len] != ':')
			++len;
		*ptr_exe = ft_substrjoin_with_slash(path + start, av0, len);
		if (!*ptr_exe)
			return (E_MLC);
		if (!access(*ptr_exe, F_OK))
			return (NO_ERR);
		free(*ptr_exe);
		start += len;
		if (path[start])
			++start;
	}
	*ptr_exe = 0;
	return (NO_ERR);
}

t_builin_fct	is_a_builtin(char *av0)
{
	static const t_builin_fct	fct_builtin[] = {bi_echo, bi_exit, bi_cd,
		bi_pwd, bi_env, bi_export, bi_unset, bi_alias, 0};
	static char					*str_builtin[] = {"echo", "exit", "cd", "pwd",
				"env", "export", "unset", "alias", 0};
	uint64_t					i;

	if (!av0)
		return (0);
	i = 0;
	while (str_builtin[i])
	{
		if (!ft_strcmp(av0, str_builtin[i]))
			return (fct_builtin[i]);
		++i;
	}
	return (0);
}

uint64_t	find_exe(char **ptr_exe, t_builin_fct *fct_blti, char *av0, char *path)
{
	if (!av0)
		return (NO_ERR);
	*fct_blti = is_a_builtin(av0);
	if (*fct_blti)
		return (NO_ERR);
	if (!path || ft_strchr(av0, '/'))
	{
		if (!access(av0, F_OK))
			*ptr_exe = av0;
		return (NO_ERR);
	}
	return (find_exe_int_path(ptr_exe, av0, path));
}
