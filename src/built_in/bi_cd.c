/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:36:38 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/27 18:15:25 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

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

int	internal_cd(char *to_cd, int fdout, t_ms *ms, int to_print_newpwd)
{
	const char	*cont_pwd = find_content_var("PWD", ms->env.tab);
	char		*joined;
	char		*pwd;

	joined = 0;
	if (!to_cd || !to_cd[0])
		return (0);
	if (!chdir(to_cd))
	{
		joined = ft_strjoin("OLDPWD=", (char *)cont_pwd);
		if (!joined || add_var_env(&ms->env, joined))
			return (ms->errors |= E_MLC, 1);
		joined = (free(joined), (char *)0);
		pwd = getcwd(0,0);
		if (pwd)
			joined = ft_strjoin("PWD=", pwd);
		if (!joined  || add_var_env(&ms->env, joined))
			return (free(pwd), ms->errors |= E_MLC, 1);
		(free(pwd), free(joined));
		if (to_print_newpwd)
			return (print_newpwd(find_content_var("PWD", ms->env.tab),
				fdout, ms));
		return (0);
	}
	return (ms_c_perror(ms->pname, "cd", to_cd), 1);
}

int	cd_oldpwd(t_ms *ms, int fdout)
{
	const char *oldpwd = find_content_var("OLDPWD",ms->env.tab);

	if (!oldpwd)
		return (print_error(ms->pname, "cd: OLDPWD not set"), 1);
	return (internal_cd((char *)oldpwd, fdout, ms, 1));
}

int	cd_ac_eq_1(t_ms *ms, int fdout)
{
	const char *home = find_content_var("HOME",ms->env.tab);
 
	if (!home)
		return (print_error(ms->pname, "cd: HOME not set"), 1);
	return (internal_cd((char *)home, fdout, ms, 0));
}

int	bi_cd(int ac, char **av, int fds[2], t_ms *ms)
{
	if (ac >= 3)
		return (print_error(ms->pname, "cd: too many arguments"), 1);
	if (ac == 1)
		return (cd_ac_eq_1(ms, fds[PIPE_WRITE]));
	if (!ft_strcmp("-", av[1]))
		return (cd_oldpwd(ms, fds[PIPE_WRITE]));
	return (internal_cd(av[1], fds[PIPE_WRITE], ms, 0));
}

// 1 If  no directory operand is given and the HOME environment variable is empty or undefined, the default behavior is imple‐
//            mentation-defined and no further steps shall be taken.

//         2. If no directory operand is given and the HOME environment variable is set to a non-empty value, the cd utility shall  be‐
//            have as if the directory named in the HOME environment variable was specified as the directory operand.

//         3. If the directory operand begins with a <slash> character, set curpath to the operand and proceed to step 7.

//         4. If the first component of the directory operand is dot or dot-dot, proceed to step 6.

//         5. Starting  with the first pathname in the <colon>-separated pathnames of CDPATH (see the ENVIRONMENT VARIABLES section) if
//            the pathname is non-null, test if the concatenation of that pathname, a <slash> character if that pathname  did  not  end
//            with a <slash> character, and the directory operand names a directory. If the pathname is null, test if the concatenation
//            of dot, a <slash> character, and the operand names a directory. In either case, if the resulting string names an existing
//            directory, set curpath to that string and proceed to step 7. Otherwise, repeat this step with the next pathname in CDPATH
//            until all pathnames have been tested.

//         6. Set curpath to the directory operand.enation  of  the  value of PWD, a <slash> character if the value of PWD did not end with a
//            <slash> character, and curpath.
