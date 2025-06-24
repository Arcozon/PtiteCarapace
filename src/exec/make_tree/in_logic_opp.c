/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_logic_opp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:06:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 16:41:28 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	in_pipe(t_snippet **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(PPL);
	if (!node)
		return (E_MLC);
	node->left = left;
	*to_store = node;
	if ((*lexer)->token == open_par)
		return (in_sub(goto_next(lexer), &(node->right)));
	else if (is_cmd(*lexer))
		return (in_cmd(lexer, &(node->right)));
	else
		WAIT
	return (0);
}

uint64_t	in_and(t_snippet **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(AND);
	if (!node)
		return (E_MLC);
	node->left = left;
	*to_store = node;
	if ((*lexer)->token == open_par)
		return (in_sub(goto_next(lexer), &(node->right)));
	else if (is_cmd(*lexer))
		return (in_cmd(lexer, &(node->right)));
	else
		WAIT
	return (0);
}

uint64_t	in_or(t_snippet **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(OR);
	if (!node)
		return (E_MLC);
	node->left = left;
	*to_store = node;
	if ((*lexer)->token == open_par)
		return (in_sub(goto_next(lexer), &(node->right)));
	else if (is_cmd(*lexer))
		return (in_cmd(lexer, &(node->right)));
	else
		WAIT
	return (0);
}

uint64_t	in_scol(t_snippet **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(SCOL);
	if (!node)
		return (E_MLC);
	node->left = left;
	*to_store = node;
	if (!*lexer || (*lexer)->token == closing_par)
		return (0);
	if ((*lexer)->token == open_par)
		return (in_sub(goto_next(lexer), &(node->right)));
	else if (is_cmd(*lexer))
		return (in_cmd(lexer, &(node->right)));
	else
		WAIT
	return (0);
}
