/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:07:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 17:27:22 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	bi_unset(int ac, char **av, t_env *env, int fds[2], char *pname)
{
	uint64_t	i;
	uint64_t	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (env->tab[j])
		{
			if (!ft_strncmp_weq(av[i], env->tab[j], ft_strlen(av[i])))
			{
				remove_var_env(env, j);
				break ;
			}
			++j;
		}
		++i;
	}
	return (0);
	(void)fds, (void)pname, (void)ac;
}
