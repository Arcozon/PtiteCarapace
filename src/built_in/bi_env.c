/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:27 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define E_NOSPACE 125

static inline void	err_no_space(const char *pname)
{
	if (pname)
	{
		write(2, pname, ge_strlen(pname));
		write(2, ": ", 2);
	}
	write(2, "env: write error: No space left on device\n", 42);
}

int	bi_env(int ac, char **av, int fds[2], t_ms *ms)
{
	uint64_t	i;
	int64_t		len;

	(void)ac, (void)av;
	i = 0;
	while (ms->env.tab[i])
	{
		len = ge_strlen(ms->env.tab[i]);
		if (write(fds[PIPE_WRITE], ms->env.tab[i], len) != len
			|| write(fds[PIPE_WRITE], "\n", 1) != 1)
			return (err_no_space(ms->pname), E_NOSPACE);
		++i;
	}
	return (EXIT_SUCCESS);
}
