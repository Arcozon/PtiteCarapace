/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:09:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 16:09:06 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

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
