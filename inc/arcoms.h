/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arcoms.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:16:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 10:50:56 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

#ifndef ARCOMS_H
# define ARCOMS_H

# include <unistd.h>
# include <stdlib.h>

# include "utils.h"
# include "types.h"
# include "errors.h"

# include "env.h"

# include "exec_cmds.h"
# include "exec_btree.h"

# define DEBUG(s, ...)	{fprintf(stderr, s, __VA_ARGS__); fprintf(stderr, "\n");}

# define PIPE_READ	0
# define PIPE_WRITE	1

int	bi_env(int ac, char **av, t_env *env, int fds[2], const char *pname);
int	bi_export(int ac, char **av, t_env *env, int fds[2], char *pname);

#endif
