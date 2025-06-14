/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:59:47 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 15:39:54 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "types.h"

# define BASE_ENV_SIZE	512

struct s_env
{
	char		**tab;

	uint64_t	last_mty;
	uint64_t	ttsize;
};

uint64_t	init_env(t_env *env, char *envp[]);
uint64_t	add_var_env(t_env *env, char *to_add);
void		remove_var_env(t_env *env, size_t to_remove);
void		free_env(t_env *env);

#endif
