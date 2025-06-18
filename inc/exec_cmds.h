/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:20:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/18 11:28:53 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMDS_H
# define EXEC_CMDS_H

# include "types.h"

struct s_exe_hdoc
{
	char		*limiter;
	uint8_t		to_expand:1;
	char		**env;
	
	int			hdoc_fd;
	int			pipes[2][2];
	pid_t		pid;
	
	char		*vname;
	size_t		i_name;
	size_t		mlen_env;
	size_t		mlen_hdoc;
	int			act_len;

	char		c;
	int			br;

	char		*pname;

	uint64_t	errors;
};

void	heredoc_handle_dollar(char c, t_x_hdoc *hdoc);
int		launch_heredocs(t_snippet *delims, char **env, t_ms minishell, char *pname);
int		read_stdin_no_exp(t_x_hdoc *hdoc, int fdin);

struct s_cmd
{
	int			(*builtin)(int, char *[], char *[]); //proply ll change
	uint8_t		in_fork:1;
	char		*path_cmd;
	char		**argv_cmd;

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
