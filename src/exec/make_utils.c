/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:43:09 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 12:03:12 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	add_back_lexer(t_snippet **lexer, t_snippet *to_add)
{
	while (*lexer)
		lexer = &((*lexer)->next);
	*lexer = to_add;
}

t_snippet	**goto_next(t_snippet **lexer)
{
	t_snippet	*to_free;
	
	to_free = *lexer;
	*lexer = (*lexer)->next;
	if (!g_lexer_id[to_free->token])
	{
		free(to_free->ptr);
		free(to_free);
	}
	return (lexer);
}

void	store_cmd(t_snippet **lexer, t_cmd *cmd)
{
	t_snippet	*to_store;

	to_store = *lexer;
	goto_next(lexer);
	to_store->next = 0;
	if (g_lexer_id[to_store->token] == F_HEREDOC)
		add_back_lexer(&cmd->heredoc, to_store);
	if (g_lexer_id[to_store->token] == F_S_REDIR)
		add_back_lexer(&cmd->redirs, to_store);
	if (g_lexer_id[to_store->token] == F_WORD)
		add_back_lexer(&cmd->sn_argv, to_store);
}

int	is_heredoc(t_snippet *lexer)
{	
	return (g_lexer_id[lexer->token] & F_HEREDOC);
}

int	is_simple_redir(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] & F_S_REDIR);
}

int	is_redir(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] & M_A_REDIR);
}

int	is_cmd(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] & M_IN_CMD);
}

int	is_useless_token(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] == F_USELESS);
}
