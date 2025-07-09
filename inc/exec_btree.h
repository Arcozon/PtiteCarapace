/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_btree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:18:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/09 13:12:25 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BTREE_H
# define EXEC_BTREE_H

# include "types.h"

# define PTR_CMD_NOT_FOUND	0
# define PTR_NO_SUCH_FILE	1

# define STT_CMD_NOT_FOUND	127
# define STT_SIG_BASE		0x80

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
void			exec_ppl_cmd(t_base *node, t_ms *ms, int to_close);

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
	t_snippet		*sn_argv_exp;

	pid_t			pid;

	int				rstatus;
	uint64_t		errors;
};

uint64_t		open_redir(t_cmd *cmd, t_ms *ms);
uint64_t		create_argv(t_cmd *cmd, t_ms *ms);
t_builin_fct	is_a_builtin(char *av0);
uint64_t		find_exe(char **ptr_exe, t_builin_fct *fct_blti,
					char *av0, char *path);
uint64_t		execve_cmd(t_cmd *cmd, t_ms *ms);
uint32_t		is_non_executable(char *path_exe);
uint32_t		ft_is_file_lnk(const char *path_file);


void			launch_subsh(t_base *node, t_ms *ms, int to_close);
void			exec_scol(t_base *node, t_ms *ms);
void			exec_and(t_base *node, t_ms *ms);
void			exec_or(t_base *node, t_ms *ms);
void			exec_subsh(t_base *node, t_ms *ms);
void			exec_simple_cmd(t_base *node, t_ms *ms);
void			exec_ppl(t_base *node, t_ms *ms);
void			exec_node(t_base *node, t_ms *ms);
void			exec_start(t_ms *ms, t_snippet **lexer);

#endif
