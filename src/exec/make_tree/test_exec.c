/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:51:38 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 15:05:03 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	lexer_add_back(t_snippet **lexer, enum e_token token)
{
	const char *tab[] = {"cmd1", "cmd2", "cmd3", "cmd4", "cmd5"};
	static int i = 0;
	while (*lexer)
		lexer = &((*lexer)->next);
	*lexer = ft_calloc(sizeof(t_snippet));
	(*lexer)->token = token;
	if (token == word)
		(*lexer)->ptr = ft_strdup(tab[i++  % 5]);
	if (token == redir_in)
		(*lexer)->ptr = ft_strdup("in");
	if (token == redir_out)
		(*lexer)->ptr = ft_strdup("out");
	if (token == here_doc)
		(*lexer)->ptr = ft_strdup("here");
	if (token == append)
		(*lexer)->ptr = ft_strdup("app");
}

t_snippet	*mk_lexer(char *lst)
{
	t_snippet *lexer;

	lexer = 0;
	for (;*lst; ++lst)
	{
		if (*lst == 'W')
			lexer_add_back(&lexer, word);
		else if (*lst == '(')
			lexer_add_back(&lexer, open_par);
		else if (*lst == ')')
			lexer_add_back(&lexer, closing_par);
		else if (*lst == '|')
			lexer_add_back(&lexer, pipe_delim);
		else if (*lst == '&')
			lexer_add_back(&lexer, and);
		else if (*lst == 'O')
			lexer_add_back(&lexer, or);
		else if (*lst == '<')
			lexer_add_back(&lexer, redir_in);
		else if (*lst == '>')
			lexer_add_back(&lexer, redir_out);
		else if (*lst == 'H')
			lexer_add_back(&lexer, here_doc);
		else if (*lst == 'A')
			lexer_add_back(&lexer, append);
		else if (*lst == ';')
			lexer_add_back(&lexer, semicolon);
	}
	return (lexer);
}

int main(void)
{
	t_snippet	*lexer;
	t_base *node;

	lexer = mk_lexer("<HA>|HA<A>H");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);

	lexer = mk_lexer("W|(W|W|W)|W");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);

	lexer = mk_lexer("((W)&W);(W;);");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);

	lexer = mk_lexer("(WOW&(W&W))");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);

	lexer = mk_lexer("W|W");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);
	
	lexer = mk_lexer("W&W|W");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);
	
	lexer = mk_lexer("((W;W)|W)");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);

	lexer = mk_lexer("((WH|WOW)<>HH);WOW&(<|>)");
	debug_lexer(lexer);
	make_base(&lexer, &node);
	debug_tree(node);free_node(&node);
}
