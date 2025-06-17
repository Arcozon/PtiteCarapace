/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:10:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 16:34:33 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_TREE_H
# define MAKE_TREE_H

# include "types.h"
# include "exec_cmds.h"

# define F_USELESS	0b000
# define F_S_REDIR	0b001
# define F_HEREDOC	0b010
# define F_WORD		0b100

# define M_A_REDIR	0b011
# define M_IN_CMD	0b111

static const int	g_lexer_id[] = {F_WORD, F_S_REDIR, F_S_REDIR, F_HEREDOC,
	F_S_REDIR, F_USELESS, F_USELESS, F_USELESS,
	F_USELESS, F_USELESS, F_USELESS};

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
	closing_par
};

struct s_node
{
	enum e_token	token;
	char			*ptr;
	t_snippet		*next;
};

struct s_base
{
	enum
	{
		SCOL,
		AND,
		OR,
		PPL,
		CMD,
		SUB
	}	e_type;
	t_base	*left;
	t_base	*right;

	t_cmd	cmd;

	int		fd_in;
	int		fd_out;
};

t_base	*mlc_base(int type);

uint64_t	make_base(t_snippet **lexer, t_base **to_store);

uint64_t	in_cmd(t_snippet **lexer, t_base **to_store);
uint64_t	in_sub(t_snippet **lexer, t_base **to_store);
uint64_t	in_or(t_snippet **lexer, t_base *left, t_base **to_store);
uint64_t	in_and(t_snippet **lexer, t_base *left, t_base **to_store);
uint64_t	in_scol(t_snippet **lexer, t_base *left, t_base **to_store);
uint64_t	in_pipe(t_snippet **lexer, t_base *left, t_base **to_store);

t_snippet	**goto_next(t_snippet **lexer);
void		add_back_lexer(t_snippet **lexer, t_snippet *to_add);
void		store_cmd(t_snippet **lexer, t_cmd *cmd);

int			is_cmd(t_snippet *lexer);
int			is_redir(t_snippet *lexer);
int			is_simple_redir(t_snippet *lexer);
int			is_heredoc(t_snippet *lexer);
int			is_useless_token(t_snippet *lexer);

void		debug_lexer(t_snippet *lexer);
void		debug_tree(t_base *node);

void		free_node(t_base **pnode);

#endif
