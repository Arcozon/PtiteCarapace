/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arcoms.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:16:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 19:01:35 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCOMS_H
# define ARCOMS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include "utils.h"
# include "types.h"
# include "errors.h"

# include "env.h"
# include "built_in.h"

# include "exec_cmds.h"
# include "exec_btree.h"

# define DEBUG(s, ...)	{fprintf(stderr, s, __VA_ARGS__); fprintf(stderr, "\n");}

# define PIPE_READ	0
# define PIPE_WRITE	1

#endif
