/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_btree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:18:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:51:12 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BTREE_H
# define EXEC_BTREE_H

# include "types.h"

struct s_exe_hdoc
{
	char		*limiter;
	uint8_t		to_expand:1;

	char		**env;
	uint8_t		qmark_value;

	int			pipes[2][2];

	char		*vname;
	uint64_t	i_vname;
	uint64_t	mlen_hdoc;
	int			act_len;

	char		c;
	int			br;

	char		*pname;

	uint64_t	errors;
};

int				hdoc_read_fd_exp(int fdin, int fdout, t_x_hdoc *hdoc);
void			heredoc_handle_dollar(char c, t_x_hdoc *hdoc);
int				launch_heredocs(t_snippet *delims, char **env, t_ms *ms);
int				read_stdin_no_exp(t_x_hdoc *hdoc, int fdin);
void			exec_ppl_cmd(t_base *node, t_ms *ms);

struct s_cmd
{
	t_builin_fct	builtin;
	char			*path_exe;
	char			**argv_cmd;

	int				fd_in;
	int				fd_out;

	t_snippet		*heredoc;
	t_snippet		*redirs;
	t_snippet		*sn_argv;

	pid_t			pid;

	int				rstatus;
	uint64_t		errors;
};

uint64_t		open_redir(t_cmd *cmd, char *pname);
uint64_t		create_argv(t_cmd *cmd, t_ms *ms);
char			*find_path(char **env);
t_builin_fct	is_a_builtin(char *av0);
uint64_t		find_exe(char **ptr_exe, t_builin_fct *fct_blti,
					char *av0, char *path);
uint64_t		execve_cmd(t_cmd *cmd, t_ms *ms);

void			launch_subsh(t_base *node, t_ms *ms);
void			exec_scol(t_base *node, t_ms *ms);
void			exec_and(t_base *node, t_ms *ms);
void			exec_or(t_base *node, t_ms *ms);
void			exec_subsh(t_base *node, t_ms *ms);
void			exec_simple_cmd(t_base *node, t_ms *ms);
void			exec_ppl(t_base *node, t_ms *ms);
void			exec_node(t_base *node, t_ms *ms);

#endif
