/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:41:32 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/15 10:52:48 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "parsing.h"

# include "snippet.h"

# include "prompt.h"
# include "env.h"
# include "built_in.h"

# include "signal_handling.h"
# include "make_tree.h"
# include "exec_btree.h"

# include "libftprintf.h"
# include "get_next_line.h"
# include "ga_printf.h"
# include "utils.h"
# include "types.h"
# include "errors.h"

# define MS_HISTORY ".ms_history"
# define MS_RC ".minishellrc"

# define PIPE_READ	0
# define PIPE_WRITE	1

struct s_ms
{
	char			*pname;

	char			prompt[PROMPT_SIZE];
	char			prompt2[PROMPT_SIZE];
	t_hash_table	table;
	t_snippet		*lexer;

	t_base			*exec_tree;

	t_env			env;
	uint8_t			status;

	int				msrc_fd;
	int				history_fd;
	char			*prev_cmdline;
	struct termios	term_settings;

	uint64_t		errors;
};

#endif
