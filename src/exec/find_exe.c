/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:32:04 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 11:16:41 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

// 0 is not file
uint32_t	ft_is_file_lnk(const char *path_file)
{
	struct stat	bufstat;

	if (stat(path_file, &bufstat) < 0)
		return (0);
	return (((bufstat.st_mode & __S_IFMT)
		& (__S_IFREG | __S_IFLNK)) != 0);
}

uint64_t	find_exe_int_path(char **ptr_exe, char *av0, char *path)
{
	uint64_t	start;
	uint64_t	len;

	start = 0;
	while (1)
	{
		len = 0;
		while (path[start + len] && path[start + len] != ':')
			++len;
		*ptr_exe = ft_substrjoin_with_slash(path + start, av0, len);
		if (!*ptr_exe)
			return (E_MLC);
		if (!access(*ptr_exe, F_OK) && ft_is_file_lnk(*ptr_exe))
			return (NO_ERR);
		free(*ptr_exe);
		start += len;
		if (path[start])
			++start;
		else
			break ;
	}
	*ptr_exe = PTR_CMD_NOT_FOUND;
	return (NO_ERR);
}

t_builin_fct	is_a_builtin(char *av0)
{
	static const t_builin_fct	fct_builtin[] = {bi_echo, bi_clear, bi_exit, bi_cd,
		bi_pwd, bi_env, bi_export, bi_unset, bi_alias, bi_status, 0};
	static char					*str_builtin[] = {"echo", "clear", "exit", "cd", "pwd",
		"env", "export", "unset", "alias", "status", 0};
	uint64_t					i;

	if (!av0)
		return (0);
	i = 0;
	while (str_builtin[i])
	{
		if (!ge_strcmp(av0, str_builtin[i]))
			return (fct_builtin[i]);
		++i;
	}
	return (0);
}

uint64_t	find_exe(char **ptr_exe, t_builin_fct *fct_blti,
	char *av0, char *path)
{
	if (!av0)
		return (NO_ERR);
	*fct_blti = is_a_builtin(av0);
	if (*fct_blti)
		return (NO_ERR);
	if (!path || !path[0] || ge_strchr(av0, '/'))
	{
		*ptr_exe = (char *)PTR_NO_SUCH_FILE; 
		if (!access(av0, F_OK))
			*ptr_exe = av0;
		return (NO_ERR);
	}
	return (find_exe_int_path(ptr_exe, av0, path));
}
