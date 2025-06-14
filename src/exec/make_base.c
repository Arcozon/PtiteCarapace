/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:32:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 23:53:34 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

char g[1];
# define WAIT {fprintf(stderr,"---WAIT");read(0, g, 1);}

enum e_token
{
	DONE = 0,
    word,
    redir_in,
    redir_out,
    here_doc,
    append,
    pipe_delim,
    or,
    and,
    semicolon,
    open_par,
    closing_par
};

typedef int t_lexer;

typedef struct s_plexer
{
	t_lexer		*lexer;
	uint64_t	len;
}	t_plexer;

t_lexer	**goto_next(t_lexer **lexer)
{
	*lexer += 1;
	return lexer;
}

t_base	*mlc_base(int type)
{
	t_base	*new;

	new = ft_calloc(sizeof(t_base));
	if (!new)
		return (0);
	new->fd_out = 1;
	new->e_type = type;
	return (new);
}

t_base	*in_cmd(t_lexer **lexer, t_base *parent);	//-> && || | ; ) DONE
t_base	*in_sub(t_lexer **lexer, t_base *parent);	//-> ( cmd
t_base	*in_or(t_lexer **lexer, t_base *left);	// ( cmd
t_base	*in_and(t_lexer **lexer, t_base *left);	// ( cmd
t_base	*in_scol(t_lexer **lexer, t_base *left);	// ( cmd
t_base	*in_pipe(t_lexer **lexer, t_base *left);	// ( cmd


t_base	*in_cmd(t_lexer **lexer, t_base *parent)
{
	t_base	*node;

	printf("CMD\n");
	if (!**lexer)
		return (0);
	node = mlc_base(CMD);
	if (!parent)
		parent = node;
	while (**lexer != closing_par && **lexer != or && **lexer != and && **lexer != semicolon && **lexer != pipe_delim && **lexer != DONE)
		goto_next(lexer);
	if (**lexer == closing_par)
		return (node);
	if (**lexer == DONE)
		return (node);
	if (**lexer == and)
		return (in_and(goto_next(lexer), parent));
	if (**lexer == or)
		return (in_or(goto_next(lexer), parent));
	if (**lexer == semicolon)
		return (in_scol(goto_next(lexer), parent));
	if (**lexer == pipe_delim)
		return (in_pipe(goto_next(lexer), parent));
	return (node);
}

t_base	*in_subshell(t_lexer **lexer, t_base *parent) 
{
	t_base	*node;

	printf("SUBSHELL\n");
	if (!**lexer)
		return (0);
	node = mlc_base(SUB);
	if (!parent)
		parent = node;
	if (**lexer == open_par)
		node->left = in_subshell(goto_next(lexer), 0);
	else	
		node->left = in_cmd(goto_next(lexer), 0);
	if (**lexer == closing_par)
	{
		printf("END SUBSHELL\n");
		goto_next(lexer);
		if (**lexer == and)
			node = in_and(goto_next(lexer), node);
		else if (**lexer == or)
			node = in_or(goto_next(lexer), node);
		else if (**lexer == semicolon)
			node = in_scol(goto_next(lexer), node);
		else if (**lexer == pipe_delim)
			node = in_pipe(goto_next(lexer), node);
	}
	else
		printf("jksdhvafdjkasfvjkasvdfjkvahsdfjkhdsvaf\n");
	// exit(1);
	return (node);
}

t_base	*in_pipe(t_lexer **lexer, t_base *left)
{
	t_base	*node;

	printf("PIPE\n");
	if (!**lexer)
		return (0);
	node = mlc_base(PPL);
	node->left = left;
	if (**lexer == open_par)
		node->right = in_subshell(goto_next(lexer), 0);
	else
		node->right = in_cmd(lexer, 0);
	return (node);
}

t_base	*in_and(t_lexer **lexer, t_base *left)
{
	t_base	*node;

	printf("AND\n");
	if (!**lexer)
		return (0);
	node = mlc_base(AND);
	node->left = left;
	if (**lexer == open_par)
		node->right = in_subshell(goto_next(lexer), 0);
	else
		node->right = in_cmd(lexer, 0);
	return (node);
}

t_base	*in_or(t_lexer **lexer, t_base *left)
{
	t_base	*node;

	printf("OR\n");
	if (!**lexer)
		return (0);
	node = mlc_base(OR);
	node->left = left;
	if (**lexer == open_par)
		node->right = in_subshell(goto_next(lexer), 0);
	else
		node->right = in_cmd(lexer, 0);
	return (node);
}

t_base	*in_scol(t_lexer **lexer, t_base *left)
{
	t_base	*node;

	printf("SEMI\n");
	node = mlc_base(SCOL);
	node->left = left;
	if (!**lexer || **lexer == closing_par)
		return (node);
	// WAIT
	if (**lexer == open_par)		
		node->right = in_subshell(goto_next(lexer), 0);
	else
		node->right = in_cmd(lexer, 0);
	return (node);
}

t_base	*make_base(t_lexer **lexer)
{
	t_base	*base;

	base = 0;
	while (**lexer)
	{
		if (**lexer == open_par)
			base = in_subshell(goto_next(lexer), base);
		else
			base = in_cmd(lexer, base);
		if (**lexer == and)
			base = in_and(goto_next(lexer), base);
		else if (**lexer == or)
			base = in_or(goto_next(lexer), base);
		else if (**lexer == semicolon)
			base = in_scol(goto_next(lexer), base);
		else if (**lexer == pipe_delim)
			base = in_pipe(goto_next(lexer), base);
	}
	return (base);
}

void	pipicaca(t_base *node)
{
	return ;
	static char *trad[] = (char*[]){"SCOL", "AND", "OR", "PPL","CMD",
		"SUB"};
	
	fprintf(stderr, "%4s		%p\n", trad[node->e_type], node);
	fprintf(stderr, "%p | %p\n", node->left, node->right);
	WAIT
}

void	debug_tree_rec(t_base *node)
{
	if (!node)
	{
		printf("Done");
		return ;
	}
	pipicaca(node);
	if (node->e_type == CMD)
	{
		printf("cmd");
		return ;
	}
	else if (node->e_type == SUB)
	{
		printf("(");
		debug_tree_rec(node->left);
		printf(")");
		return ;
	}
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
}

void	debug_tree(t_base *node)
{
	printf("TREE: ");
	debug_tree_rec(node);
	printf("\n\n\n");
}

void	debug_lexer(t_lexer *lexer)
{
	static char *trad[] = (char*[]){"DONE", "word", "<", ">","<<",
		">>", "|", "||", "&&", ";", "(", ")"};
	
	printf("LEXER: ");
	for (int i = 0; lexer[i]; ++i)
		printf("%s ", trad[lexer[i]]);
	printf("\n");
}

int main(void)
{
	t_lexer	*lexer;
	t_base *node;

	lexer = (int[]){word,semicolon,open_par,word,semicolon,closing_par ,semicolon,DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);

	lexer = (int[]){open_par,open_par,word,closing_par,and, word, closing_par,semicolon,open_par,word, semicolon,closing_par ,DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);

	lexer = (int[]){open_par, word,or, word, and, open_par,word, and, word,  closing_par,  closing_par, DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);

	lexer = (int[]){word, pipe_delim, word, DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);
	
	lexer = (int[]){word, and, word, and, word, DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);
	
	lexer = (int[]){open_par,open_par, word, semicolon, word,closing_par, pipe_delim, word, closing_par,DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);
}


// cmd && a || (b && c)
