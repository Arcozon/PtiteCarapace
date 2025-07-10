/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:41:59 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/10 17:40:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <limits.h>
# include <unistd.h>

# include "libftprintf.h"
// # include "arcoms.h"
# include "types.h"

# define SYNTAXE ": syntax error near unexpected token "
# define SEP "| \t\v\n\r\f&<>;()"
# define OPENER "'\""
# define MS_HISTORY ".ms_history"
# define MS_RC ".minishellrc"
# define FORBIDDEN_CHAR_ALIAS " \t\n\v\r\f/!@#$*&():"
# define BUF_SIZE 511

typedef struct s_pair
{
	int				len;
	char			*key;
	char			*value;
	struct s_pair	*next;
}	t_pair;

typedef struct s_pipe_buf
{
	int					fd;
	int					len;
	struct s_pipe_buf	*next;
}	t_exp;

enum e_token
{
	word,
	redir_in,
	redir_out,
	here_doc,
	append,
	pipe_delim,
	or,
	and,
	semicolon,
	open_par,
	closing_par,
	env_var
};

typedef struct s_node
{
	enum e_token	token;
	char			*ptr;
	struct s_node	*next;
}	t_snippet;

# define TABLE_SIZE 512 // Always 2^n to keep the speed

typedef struct s_hash_table
{
	t_pair	*bucket[TABLE_SIZE];
}	t_hash_table;

//Snippet

t_snippet	*new_snip(enum e_token token, char *ptr);
void		pop_snip(t_snippet **head, t_snippet *to_pop);
bool		add_to_snip_lst(t_snippet **head, enum e_token token, char *ptr);
void		insert_snip(t_snippet *node, t_snippet *to_insert);
t_snippet	*get_last_snip(t_snippet *lst);
void		free_snip_lst(t_snippet *lst);
bool		expand_snip(t_snippet **head, t_snippet *to_expand,
				t_ms *ms, bool one_block);
t_snippet	*wildcard(char *raw_pattern);
bool		replace_wildcards(t_snippet **head);

//Utils

char		*pass_whitespace(char *str);
int			get_exit_value(int status);
bool		is_child(pid_t pid);
char		*_basename(char *str);
void		print_until(char *str, char c, int fd);
bool		dollar_n_sep(char c);
bool		simple_sep(char c);
bool		dollar_sep_quote(char c);

//History

int			ms_get_history_fd(char **ptr_oldcmd);
void		ms_add_history(char *str, int fd, char **ptr_oldcmd);
void		trim_trailling_ws(char *str);

//Signal

void		sigint_handler(int sig);
void		ms_handler(int signum);
void		set_sigchild_handler(int fds_to_close[2]);
//bool	ms_set_sighandler(void);

//Parsing 

int			get_cmd_line_fd(int	*fd, t_ms *ms);

void		parse_rc(t_ms *ms);
void		parse_rc_file(t_ms *ms, char *filename);
char		*expand(char **env, char *var_name, int len);
bool		is_statement_open(char *str);
bool		get_fd(int *fd);
void		free_table(t_hash_table *table);
int			_hash(char *key, int len);
t_pair		*get_pair(t_hash_table *table, char *key, int len);
void		set_pair(t_hash_table *table, t_pair *pair);
t_pair		*create_pair(char *str);
void		remove_pair(t_hash_table *table, t_pair *pair);

bool		is_redir(enum e_token token);
bool		is_cntl_op(enum e_token token);
bool		is_syntaxe_ok(enum e_token prev, enum e_token token);
bool		check_syntaxe(t_snippet *lst, char *exe);
bool		replace_aliases(t_snippet **head, t_hash_table *table);
bool		replace_tilde(t_snippet *lst, char *home);

int			closing_match(char *ptr);
int			find_closing_bracket(char *opening_bracket);
int			word_len(char *str, bool (*is_sep)(char ), int len);
int			get_wlen(char *ptr, int len);
int			dollar_len(char *str);
bool		is_only_wildcard(char *str);
void		pop_non_matching_files(t_list **head, char **patterns, char *raw_p);
void		take_off_hidden_files(t_list **head);
t_list		*get_all_files(void);
int			ft_strlen_without_q(char *str);
int			ft_strncmp_without_q(char *s_w_q, char *cmp, int len_w_q);
char		*ft_strnstr_without_q(const char *big, const char *l, size_t len);

//snip

t_snippet	*new_snip(enum e_token token, char *ptr);
t_snippet	*get_last_snip(t_snippet *lst);
void		pop_snip(t_snippet **head, t_snippet *to_pop);
bool		add_to_snip_lst(t_snippet **head, enum e_token token, char *ptr);
void		insert_snip(t_snippet *node, t_snippet *to_insert);
void		free_snip_lst(t_snippet *lst);

//gnl_utils

bool		add_in_list(char buffer[], t_list **head);
int			read_null_terminated(int fd, char *buffer, int buffer_size);
bool		closed_word(char const buffer[], char *quote_ptr, int *bracket_ptr);

bool		is_opened(char *str);
int			find_closing_bracket(char *opening_bracket);
int			dollar_len(char *str_dollar);
// void		expand_env_var(char **env, char *varname, int len);

void		expand_token(char *ptr, t_ms *ms, int len, char scope);
t_snippet	*lexer(char *str);
void		optimize_lst(t_snippet **head);

void		write_without_quote(char *str, int len);
size_t		write_snip(char *str, char *quote, int len);
char		*expand(char **env, char *var_name, int len);

#endif
