/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:31:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 15:14:01 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

static char *trad[] = (char*[]){"word", "<", ">","<<",
		">>", "|", "||", "&&", ";", "(", ")"};

void	pipicaca(t_base *node)
{
	return ;
	static char *btrad[] = (char*[]){"SCOL", "AND", "OR", "PPL","CMD",
		"SUB"};
	
	fprintf(stderr, "%4s		%p\n", btrad[node->e_type], node);
	fprintf(stderr, "%p | %p\n", node->left, node->right);
	WAIT
}

void	debug_tree_rec(t_base *node)
{
	t_snippet	*l;

	if (!node)
		return ;
	pipicaca(node);
	if (node->e_type == CMD)
	{
		l = node->cmd.sn_argv;
		for (;l;l = l->next)
			printf("%s", l->ptr);
		printf("'");
		l = node->cmd.heredoc;
		for (;l;l = l->next)
			printf("%s",l->ptr);
		printf("'");
		l = node->cmd.redirs;
		for (;l;l = l->next)
			printf("%s",l->ptr);
		printf(">");
		return ;
	}
	else if (node->e_type == SUB)
	{
		printf("(");
		debug_tree_rec(node->left);
		l = node->cmd.heredoc;
		for (;l;l = l->next)
			printf("%s",l->ptr);
		printf("'");
		l = node->cmd.redirs;
		for (;l;l = l->next)
			printf("%s",l->ptr);
		printf(">");
		printf(")");
		return ;
	}
	if (node->e_type != PPL)
		printf("{");
	else
		printf("[");
	debug_tree_rec(node->left);
	if (node->e_type == AND)
		printf(" && ");
	else if (node->e_type == SCOL)
		printf(" ; ");
	else if (node->e_type == OR)
		printf(" || ");
	else if (node->e_type == PPL)
		printf(" | ");
	debug_tree_rec(node->right);
	if (node->e_type != PPL)
		printf("}");
	else
		printf("]");
}

void	debug_tree(t_base *node)
{
	printf("--TREE: ");
	debug_tree_rec(node);
	printf("\n\n\n");
}

void	debug_lexer(t_snippet *lexer)
{
	printf("--LEXER: ");
	for (; lexer; lexer = lexer->next)
		printf("%s ", trad[lexer->token]);
	printf("\n");
}
