/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:59:32 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:53:15 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	realloc_env(t_env *env)
{
	char	**new_env;

	new_env = ft_calloc(sizeof(char *) * (env->ttsize * 2 + 1));
	if (!new_env)
		return (E_MLC);
	ft_memcpy(new_env, env->tab, env->ttsize);
	free(env->tab);
	env->tab = new_env;
	env->ttsize *= 2;
	return (NO_ERR);
}

void	remove_var_env(t_env *env, size_t to_remove)
{
	if (to_remove >= env->last_mty)
		return ;
	free(env->tab[to_remove]);
	if (env->last_mty)
		env->tab[to_remove] = env->tab[env->last_mty - 1];
	env->tab[env->last_mty - 1] = 0;
	--env->last_mty;
}

static inline char	__attribute__((always_inline))	*dup_var(char *var)
{
	uint64_t	i;
	char		*new;

	i = 0;
	while (var[i])
		if (var[i++] == '=')
			return (ft_strdup(var));
	new = malloc(sizeof(char) * (i + 2));
	if (!new)
		return (0);
	new[i + 1] = 0;
	new[i] = '=';
	while (i--)
		new[i] = var[i];
	return (new);
}

uint64_t	add_var_env(t_env *env, char *to_add)
{
	uint64_t	i;
	uint64_t	len_var;

	if (env->last_mty >= env->ttsize && realloc_env(env))
		return (E_MLC);
	to_add = dup_var(to_add);
	if (!to_add)
		return (E_MLC);
	len_var = 0;
	while (to_add[len_var] != '=')
		++len_var;
	i = 0;
	while (env->tab[i] && ft_strncmp_weq(to_add, env->tab[i], len_var))
		++i;
	if (i != env->last_mty)
	{
		free(env->tab[i]);
		env->tab[i] = to_add;
	}
	else
	{
		env->tab[env->last_mty] = to_add;
		++env->last_mty;
	}
	return (NO_ERR);
}

uint64_t	init_env(t_env *env, char *envp[])
{
	env->last_mty = 0;
	env->ttsize = BASE_ENV_SIZE;
	env->tab = ft_calloc(sizeof(char *) * (BASE_ENV_SIZE + 1));
	if (!env->tab)
		return (E_MLC);
	while (*envp)
	{
		if (add_var_env(env, *envp))
			return (E_MLC);
		++envp;
	}
	return (NO_ERR);
}
