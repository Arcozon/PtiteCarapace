/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arcoms.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:16:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/06 13:56:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

#ifndef ARCOMS_H
# define ARCOMS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "debug.h"

# include "utils.h"
# include "types.h"
# include "errors.h"

# include "prompt.h"
# include "env.h"
# include "built_in.h"

# include "signal_handling.h"
# include "make_tree.h"
# include "exec_btree.h"

# include "arco_get_next_line.h"
# include "ga_printf.h"

# define MS_RL_CTRLD		1
# define MS_RL_RESTART_READ	2

# define PIPE_READ	0
# define PIPE_WRITE	1

struct s_ms
{
	char			*pname;

	char			prompt[PROMPT_SIZE];
	t_hash_table	table;
	t_snippet		*lexer;

	t_base			*exec_tree;

	t_env			env;
	uint8_t			status;
	uint64_t		errors;

	int				history_fd;
	char			*prev_cmdline;
};


#endif
