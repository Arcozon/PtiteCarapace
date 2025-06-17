/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 11:59:50 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMDS_H
# define EXE_CMDS_H

# include "types.h"

struct s_exe_heredoc
{
	char		*delimiter;
	uint8_t		to_expand:1;
	char		**env;			//can change the type

	int			hdoc_fd;
	int			pipe[2];

	size_t		mlen_env;
	size_t		mlen_hdoc;
	size_t		mlen_var;
	char		*vname;
	size_t		i_name;

	uint64_t	errors;
};

struct s_cmd
{
	int			(*builtin)(int, char *[], char *[]); //proply ll change
	uint8_t		in_fork:1;
	char		*path_cmd;
	char		*argv_cmd;

	int			fd_in;
	int			fd_out;

	t_snippet	*heredoc;
	t_snippet	*redirs;
	t_snippet	*sn_argv;

	int			in_pipe;
	int			out_pipe;

	pid_t		pid;

	uint64_t	errors;
};

#endif
