/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:59:32 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/13 17:23:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	realloc_env(t_env *env)
{
	char **new_env;

	new_env = ft_calloc(sizeof(char *) * (env->ttsize * 2 + 1));
	if (!new_env)
		return (E_MLC);
	ft_memcpy(new_env, env->env, env->ttsize);
	free(env->env);
	env->env = new_env;
	env->ttsize *= 2;
	return (NO_ERR); 
}

void	remove_var_env(t_env *env, size_t to_remove)
{
	if (to_remove >= env->last_mty)
		return ;
	free(env->env[to_remove]);
	env->env[to_remove] = env->env[env->last_mty - 1];
	env->env[env->last_mty] = 0;
	--env->last_mty;
}

static inline char	__attribute__((always_inline))	*dup_var(char *var)
{
	uint64_t	i;
	char 		*new;

	i = 0;
	while (var[i])
		if (var[i] == '=')
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
	if (env->last_mty > env->ttsize && realloc_env(env))
		return (E_MLC);
	//cjeck dup
	to_add = dup_var(to_add);
	if (!to_add)
		return (E_MLC);
	env->env[env->last_mty] = to_add;
	++env->last_mty;
	return (NO_ERR);
}

uint64_t	init_env(t_env *env, char *envp[])
{
	env->last_mty = 0;
	env->ttsize = BASE_ENV_SIZE;
	env->env = ft_calloc(BASE_ENV_SIZE);
	if (env->env)
		return (E_MLC);
	while (*envp)
	{
		if (add_var_env(env, *envp))
			return (E_MLC);
		++envp;
	}
	return (NO_ERR);
}

