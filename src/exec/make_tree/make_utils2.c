/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/08 18:11:10 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	lis_heredoc(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] & F_HEREDOC);
}

int	lis_simple_redir(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] & F_S_REDIR);
}

int	lis_redir(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] & M_A_REDIR);
}

int	lis_cmd(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] & M_IN_CMD);
}

int	lis_useless_token(t_snippet *lexer)
{
	return (g_lexer_id[lexer->token] == F_USELESS);
}
