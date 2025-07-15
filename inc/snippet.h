/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snippet.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:59:22 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:40:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNIPPET_H
# define SNIPPET_H

# include "types.h"

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

struct s_node
{
	enum e_token	token;
	char			*ptr;
	struct s_node	*next;
};

t_snippet	*lexer(char *str);

void		optimize_lst(t_snippet **head);
t_snippet	*get_last_snip(t_snippet *lst);
t_snippet	*new_snip(enum e_token token, char *ptr);
void		pop_snip(t_snippet **head, t_snippet *to_pop);
bool		add_to_snip_lst(t_snippet **head, enum e_token token, char *ptr);
void		insert_snip(t_snippet *node, t_snippet *to_insert);
t_snippet	*get_last_snip(t_snippet *lst);
bool		expand_snip(t_snippet **head, t_snippet *to_expand, t_ms *ms,
				bool one_block);
t_snippet	*wildcard(char *raw_pattern);
bool		replace_wildcards(t_snippet **head);

#endif
