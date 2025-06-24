/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:32:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 12:46:38 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	in_cmd(t_snippet **lexer, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(CMD);
	if (!node)
		return (E_MLC);
	*to_store = node;
	while (*lexer && is_cmd(*lexer))
		store_cmd(lexer, &(node->cmd));
	if (*lexer && (*lexer)->token == pipe_delim)
		return (in_pipe(goto_next(lexer), node, to_store));
	return (0);
}

uint64_t	in_sub_handle_next(t_snippet **lexer, t_base **ptr_node_left)
{
	if ((*lexer)->token == open_par && in_sub(goto_next(lexer), ptr_node_left))
		return (E_MLC);
	else if (is_cmd(*lexer) && in_cmd(lexer, ptr_node_left))
		return (E_MLC);
	else if ((*lexer)->token == and
		&& in_and(goto_next(lexer), *ptr_node_left, ptr_node_left))
		return (E_MLC);
	else if ((*lexer)->token == or
		&& in_or(goto_next(lexer), *ptr_node_left, ptr_node_left))
		return (E_MLC);
	else if ((*lexer)->token == semicolon
		&& in_scol(goto_next(lexer), *ptr_node_left, ptr_node_left))
		return (E_MLC);
	else if ((*lexer)->token == pipe_delim
		&& in_pipe(goto_next(lexer), *ptr_node_left, ptr_node_left))
		return (E_MLC);
	return (0);
}

uint64_t	in_sub(t_snippet **lexer, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(SUB);
	if (!node)
		return (E_MLC);
	*to_store = node;
	while ((*lexer)->token != closing_par)
	{
		if (in_sub_handle_next(lexer, &(node->left)))
			return (E_MLC);
	}
	if ((*lexer)->token != closing_par)
		WAIT
	goto_next(lexer);
	while (*lexer && is_cmd(*lexer))
		store_cmd(lexer, &(node->cmd));
	return (0);
}

uint64_t	make_base(t_snippet **lexer, t_base **to_store)
{
	uint64_t	error;

	error = 0;
	while (*lexer && !error)
	{
		WAIT
		if ((*lexer)->token == open_par)
			error = in_sub(goto_next(lexer), to_store);
		else if (is_cmd(*lexer))
			error = in_cmd(lexer, to_store);
		else if ((*lexer)->token == and)
			error = in_and(goto_next(lexer), *to_store, to_store);
		else if ((*lexer)->token == or)
			error = in_or(goto_next(lexer), *to_store, to_store);
		else if ((*lexer)->token == semicolon)
			error = in_scol(goto_next(lexer), *to_store, to_store);
		else if ((*lexer)->token == pipe_delim)
			error = in_pipe(goto_next(lexer), *to_store, to_store);
	}
	return (error);
}
