/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 17:48:21 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_CMDS_H
# define EXE_CMDS_H

# include "types.h"

struct s_redir
{
	char *f_name;
	enum
	{
		OUT,
		APPEND_OUT,
		IN
	}	type;
};


struct s_heredoc
{
	char	*delim;
	t_hdoc	*next;
};


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
	char		*path_cmd;
	char		*argv_cmd;

	int			fd_int;
	int			fd_out;

	t_hdoc		*heredoc;
	t_redir		*redirs;


	int			in_pipe;
	int			out_pipe;

	pid_t		pid;

	//lexer;
};

#endif
