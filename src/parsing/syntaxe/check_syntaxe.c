/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:35:26 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 18:39:09 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(enum e_token token)
{
	return (token >= redir_in && token <= append);
}

bool	is_cntl_op(enum e_token token)
{
	return (token >= pipe_delim && token <= semicolon);
}

bool	is_syntaxe_ok(enum e_token prev, enum e_token token)
{
	if (token == open_par && !is_cntl_op(prev) && prev != open_par)
		return (false);
	if (prev == open_par && (token == closing_par || is_cntl_op(token)))
		return (false);
	if (prev == semicolon && token == closing_par)
		return (true);
	if (is_cntl_op(prev) && (is_cntl_op(token) || token == closing_par))
		return (false);
	if (is_redir(prev))
		return (token == word);
	if (prev == closing_par && token == word)
		return (false);
	return (true);
}

bool	check_syntaxe(t_snippet *lst, char *exe)
{
	enum e_token	p;
	int				bracket;
	char			*pt;

	p = lst->token;
	if (is_cntl_op(p) || p == closing_par)
		return (ft_printf("%s%s`%s'\n", exe, SYNTAXE, lst->ptr), false);
	lst = lst->next;
	pt = NULL;
	bracket = (int []){0, 1}[p == open_par];
	while (lst && is_syntaxe_ok(p, lst->token))
	{
		if (lst->token == open_par || lst->token == closing_par)
			bracket += (int []){-1, 1}[lst->token == open_par];
		p = lst->token;
		pt = lst->ptr;
		lst = lst->next;
	}
	if (bracket < 0)
		return (ft_printf("%s%s`%c'\n", exe, SYNTAXE, ')'), false);
	if (lst)
		return (ft_printf("%s%s`%s'\n", exe, SYNTAXE, lst->ptr), false);
	if ((is_cntl_op(p) && p != semicolon) || is_redir(p))
		return (ft_printf("%s%s`%s'\n", exe, SYNTAXE, pt), false);
	return (true);
}
