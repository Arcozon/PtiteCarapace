/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:44:11 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/08 18:06:40 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

char	*find_content_var(char *vname, char **env)
{
	const uint64_t	len_vname = ft_strlen(vname);

	while (*env)
	{
		if (!ge_strncmp_weq(vname, *env, len_vname))
			return (*env + len_vname + 1);
		++env;
	}
	return (0);
}

static char	*ft_strjoin_weq(const char *str1, const char *str2)
{
	const uint32_t	len1 = ft_strlen(str1);
	const uint32_t	len2 = ft_strlen(str2);
	char			*res;

	res = malloc(sizeof(char) * (len1 + 1 + len2 + 1));
	if (!res)
		return (0);
	ft_memcpy(res, str1, len1);
	res[len1] = '=';
	ft_memcpy(res + len1 + 1, str2, len2);
	res[len1 + 1 + len2] = 0;
	return (res);
}

__attribute__((always_inline))
static inline void	increase_env_var(t_env *env, char *to_inc)
{
	const char	*cto_inc = find_content_var(to_inc, env->tab);
	int			val_inc;
	char		*itoa_shlvl;
	char		*to_export;

	val_inc = 0;
	if (cto_inc)
		val_inc = ft_atoi(cto_inc);
	if (val_inc < 0)
		val_inc = 0;
	++val_inc;
	itoa_shlvl = ft_itoa(val_inc);
	if (!itoa_shlvl)
		return ;
	to_export = ft_strjoin_weq(to_inc, itoa_shlvl);
	free(itoa_shlvl);
	if (!to_export)
		return ;
	add_var_env(env, to_export);
	free (to_export);
}

void	handle_shlvl(t_env *env)
{
	increase_env_var(env, SHLVL_VNAME);
}

void	handle_submslvl(t_env *env)
{
	increase_env_var(env, MSSUBSH_VNAME);
}
