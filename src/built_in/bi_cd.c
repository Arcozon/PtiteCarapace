/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:36:38 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/20 13:51:45 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_newpwd(char *newpwd, int fdout, t_ms *ms)
{
	if (write(fdout, newpwd, ft_strlen(newpwd)) < 0
		|| write(fdout, "\n", 1) < 0)
	{
		ms_perror(ms->pname, "cd: write error");
		return (1);
	}
	return (0);
}

int	change_pwd(char *to_cd, t_ms *ms)
{
	const char	*cont_pwd = find_content_var(PWD_VNAME, ms->env.tab);
	char		*joined;
	char		*new_pwd;

	new_pwd = getcwd(0, 0);
	if (!new_pwd)
	{
		print_error_2(ms->pname, "cd", "getcwd error");
		new_pwd = ft_substrjoin_with_slash((char *)cont_pwd,
				to_cd, ft_strlen(cont_pwd));
	}
	if (!new_pwd)
		return (ms->errors |= E_MLC, 1);
	joined = ft_strjoin(PWD_VNAME"=", new_pwd);
	free(new_pwd);
	if (!joined)
		return (ms->errors |= E_MLC, 1);
	if (add_var_env(&ms->env, joined))
		return (free(joined), ms->errors |= E_MLC, 1);
	free(joined);
	return (0);
}

int	internal_cd(char *to_cd, int fdout, t_ms *ms, int to_print_newpwd)
{
	const char	*cont_pwd = find_content_var(PWD_VNAME, ms->env.tab);
	char		*joined;

	if (!to_cd)
		return (0);
	if (!chdir(to_cd) || !chdir(to_cd))
	{
		joined = ft_strjoin(OLDPWD_VNAME"=", (char *)cont_pwd);
		if (!joined || add_var_env(&ms->env, joined))
			return (free(joined), ms->errors |= E_MLC, 1);
		free(joined);
		if (change_pwd(to_cd, ms))
			return (1);
		if (to_print_newpwd)
			return (print_newpwd(find_content_var(PWD_VNAME, ms->env.tab),
					fdout, ms));
		return (0);
	}
	return (ms_c_perror(ms->pname, "cd", to_cd), 1);
}

int	cd_oldpwd(t_ms *ms, int fdout)
{
	const char	*oldpwd = find_content_var(OLDPWD_VNAME, ms->env.tab);

	if (!oldpwd)
		return (print_error_1(ms->pname, "cd: "OLDPWD_VNAME" not set"), 1);
	return (internal_cd((char *)oldpwd, fdout, ms, 1));
}

int	bi_cd(int ac, char **av, int fds[2], t_ms *ms)
{
	const char	*home = find_content_var(HOME_VNAME, ms->env.tab);

	if (ac >= 3)
		return (print_error_1(ms->pname, "cd: too many arguments"), 1);
	if (ac == 1)
	{
		if (!home)
			return (print_error_1(ms->pname, "cd: "HOME_VNAME"not set"), 1);
		return (internal_cd((char *)home, fds[PIPE_WRITE], ms, 0));
	}
	if (!ft_strcmp("-", av[1]))
		return (cd_oldpwd(ms, fds[PIPE_WRITE]));
	return (internal_cd(av[1], fds[PIPE_WRITE], ms, 0));
}
