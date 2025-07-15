/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:41:59 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:39:47 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

# define MS_RL_CTRLD		1
# define MS_RL_RESTART_READ	2

//History

int			ms_get_history_fd(char **ptr_oldcmd);
void		ms_add_history(char *str, int fd, char **ptr_oldcmd);
void		trim_trailling_ws(char *str);

//Parsing 

void		arco_rdl_child(int pipe_fds[2], t_ms *ms);
int			get_cmd_line_fd(int	*fd, t_ms *ms);

void		parse_rc_file(t_ms *ms, char *filename);
char		*expand(char **env, char *var_name, int len);
bool		is_statement_open(char *str);
t_pair		*get_pair(t_hash_table *table, char *key, int len);

bool		is_redir(enum e_token token);
bool		is_cntl_op(enum e_token token);
bool		check_syntaxe(t_snippet *lst, char *exe);
bool		replace_aliases(t_snippet **head, t_hash_table *table);

// Wildcard
int			closing_match(char *ptr);
int			word_len(char *str, bool (*is_sep)(char ), int len);
int			get_wlen(char *ptr, int len);
void		pop_non_matching_files(t_list **head, char **patterns, char *raw_p);
void		take_off_hidden_files(t_list **head);
t_list		*get_all_files(void);

bool		expand_token(char *ptr, t_ms *ms, int len, char scope);
int			write_without_quote(char *str, int len);
void		tilde_expansion(t_ms *ms, char c);
size_t		write_snip(char *str, char *quote, int len);
char		*expand(char **env, char *var_name, int len);

#endif
