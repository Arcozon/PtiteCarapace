/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:32:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 13:30:39 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "arcoms.h"

static char *trad[] = (char*[]){"word", "<", ">","<<",
		">>", "|", "||", "&&", ";", "(", ")"};

t_base	*mlc_base(int type)
{
	t_base	*new;

	new = ft_calloc(sizeof(t_base));
	if (!new)
		return (0);
	new->fd_in = -1;
	new->fd_out = -1;
	new->e_type = type;
	new->cmd.fd_in = -1;
	new->cmd.fd_out = -1;
	return (new);
}

uint64_t	in_cmd(t_snippet **lexer, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(CMD);
	if (!node)
		return (E_MLC);
	*to_store = node;
	while (*lexer && is_cmd(*lexer))
	{
		DEBUG("cmd: %s", trad[(*lexer)->token])
		store_cmd(lexer, &(node->cmd));
	}
	if (*lexer && (*lexer)->token == pipe_delim)
		return (in_pipe(goto_next(lexer), node, &(node)));
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
		if ((*lexer)->token == open_par && in_sub(goto_next(lexer), &(node->left)))
			return (E_MLC);
		else if (is_cmd(*lexer) && in_cmd(lexer, &(node->left)))
			return (E_MLC);
		else if ((*lexer)->token == and && in_and(goto_next(lexer), node->left, &(node->left)))
			return (E_MLC);
		else if ((*lexer)->token == or && in_or(goto_next(lexer), node->left, &(node->left)))
			return (E_MLC);
		else if ((*lexer)->token == semicolon && in_scol(goto_next(lexer), node->left, &(node->left)))
			return (E_MLC);
		else if ((*lexer)->token == pipe_delim && in_pipe(goto_next(lexer), node->left, &node))
			return (E_MLC);
	}
	if (*lexer && (*lexer)->token == closing_par)
	{
		goto_next(lexer);
		while (*lexer && is_cmd(*lexer))
		{
			DEBUG("SUBSHEL: %s", trad[(*lexer)->token])
			store_cmd(lexer, &(node->cmd));
		}
	}
	else
		DEBUG("ERROR")
	return (0);
}

uint64_t	in_pipe(t_snippet  **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(PPL);
	if (!node)
		return (E_MLC);
	*to_store = node;
	node->left = left;
	if ((*lexer)->token == open_par)
		return (in_sub(goto_next(lexer), &(node->right)));
	else if (is_cmd(*lexer))
		return (in_cmd(lexer, &(node->right)));
	else
		WAIT
	return (0);
}

uint64_t	in_and(t_snippet  **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(AND);
	if (!node)
		return (E_MLC);
	*to_store = node;
	node->left = left;
	if ((*lexer)->token == open_par)
		return (in_sub(goto_next(lexer), &(node->right)));
	else if (is_cmd(*lexer))
		return (in_cmd(lexer, &(node->right)));
	else
		WAIT
	return (0);
}

uint64_t	in_or(t_snippet  **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(OR);
	if (!node)
		return (E_MLC);
	*to_store = node;
	node->left = left;
	if ((*lexer)->token == open_par)
		return (in_sub(goto_next(lexer), &(node->right)));
	else if (is_cmd(*lexer))
		return (in_cmd(lexer, &(node->right)));
	else
		WAIT
	return (0);
}

uint64_t	in_scol(t_snippet  **lexer, t_base *left, t_base **to_store)
{
	t_base	*node;

	node = mlc_base(SCOL);
	if (!node)
		return (E_MLC);
	*to_store = node;
	node->left = left;
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

t_base	*make_base(t_snippet **lexer)
{
	t_base	*base;

	base = 0;
	while (*lexer)
	{
		if ((*lexer)->token == open_par)
			in_sub(goto_next(lexer), &base);
		else if (is_cmd(*lexer))
			in_cmd(lexer, &base);
		else if ((*lexer)->token == and)
			in_and(goto_next(lexer), base, &base);
		else if ((*lexer)->token == or)
			in_or(goto_next(lexer), base, &base);
		else if ((*lexer)->token == semicolon)
			in_scol(goto_next(lexer), base, &base);
		else if ((*lexer)->token == pipe_delim)
			in_pipe(goto_next(lexer), base, &base);
		else
			WAIT
	}
	return (base);
}

