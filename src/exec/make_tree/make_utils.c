/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:43:09 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 16:19:12 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

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
