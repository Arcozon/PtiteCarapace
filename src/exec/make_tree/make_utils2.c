/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/15 10:51:28 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lis_heredoc(t_snippet *lexer)
{
	const int	lexer_id[] = {F_WORD, F_S_REDIR, F_S_REDIR, F_HEREDOC,
		F_S_REDIR, F_USELESS, F_USELESS, F_USELESS,
		F_USELESS, F_USELESS, F_USELESS};

	return (lexer_id[lexer->token] & F_HEREDOC);
}

int	lis_simple_redir(t_snippet *lexer)
{
	const int	lexer_id[] = {F_WORD, F_S_REDIR, F_S_REDIR, F_HEREDOC,
		F_S_REDIR, F_USELESS, F_USELESS, F_USELESS,
		F_USELESS, F_USELESS, F_USELESS};

	return (lexer_id[lexer->token] & F_S_REDIR);
}

int	lis_redir(t_snippet *lexer)
{
	const int	lexer_id[] = {F_WORD, F_S_REDIR, F_S_REDIR, F_HEREDOC,
		F_S_REDIR, F_USELESS, F_USELESS, F_USELESS,
		F_USELESS, F_USELESS, F_USELESS};

	return (lexer_id[lexer->token] & M_A_REDIR);
}

int	lis_cmd(t_snippet *lexer)
{
	const int	lexer_id[] = {F_WORD, F_S_REDIR, F_S_REDIR, F_HEREDOC,
		F_S_REDIR, F_USELESS, F_USELESS, F_USELESS,
		F_USELESS, F_USELESS, F_USELESS};

	return (lexer_id[lexer->token] & M_IN_CMD);
}

int	lis_useless_token(t_snippet *lexer)
{
	const int	lexer_id[] = {F_WORD, F_S_REDIR, F_S_REDIR, F_HEREDOC,
		F_S_REDIR, F_USELESS, F_USELESS, F_USELESS,
		F_USELESS, F_USELESS, F_USELESS};

	return (lexer_id[lexer->token] == F_USELESS);
}
