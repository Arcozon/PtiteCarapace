/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arcoms.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:16:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:46:14 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCOMS_H
# define ARCOMS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <termios.h>
# include <signal.h>

# include "debug.h"

# include "utils.h"
# include "types.h"
# include "errors.h"

# include "env.h"
# include "built_in.h"

# include "signal_handling.h"
# include "make_tree.h"
# include "exec_btree.h"

# define PIPE_READ	0
# define PIPE_WRITE	1

# define MASK_STATUS	0xff

struct s_ms
{
	char		*pname;

	// aliases
	t_snippet	*lexer;

	t_base		*exec_tree;

	t_env		env;
	uint8_t		status;
	uint64_t	errors;
};

#endif
