/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:32:06 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/15 18:47:09 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "arcoms.h"

static char *trad[] = (char*[]){"DONE", "word", "<", ">","<<",
		">>", "|", "||", "&&", ";", "(", ")"};

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

// typedef enum e_token t_lexer;
typedef int t_lexer;

typedef struct s_plexer
{
	t_lexer		*lexer;
	uint64_t	len;
}	t_plexer;

void	debug_lexer(t_lexer *lexer);
void	debug_tree(t_base *node);

t_lexer	**goto_next(t_lexer **lexer)
{
	// free useless token { ( ) || && | ;}
	++(*lexer);
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


int	is_heredoc(t_lexer	**lexer)
{
	return (**lexer == here_doc);
}

int	is_simple_redir(t_lexer **lexer)
{
	return (**lexer == redir_out || **lexer == redir_in || **lexer == append);
}

int	is_redir(t_lexer **lexer)
{
	return (is_heredoc(lexer) || is_simple_redir(lexer));
}

int	is_cmd(t_lexer **lexer)
{
	return (**lexer == word || is_redir(lexer));
}

t_base	*in_cmd(t_lexer **lexer, t_base *parent)
{
	t_base	*node;

	if (!**lexer)
		return (0);
	node = mlc_base(CMD);
	if (!parent)
		parent = node;
	while (is_cmd(lexer))
	{
		// READ
		goto_next(lexer);
	}
	if (**lexer == closing_par)
		return (node);
	if (**lexer == DONE)
		return (node);
	if (**lexer == pipe_delim)
		return (in_pipe(goto_next(lexer), node));
	return (node);
}

t_base	*in_subshell(t_lexer **lexer, t_base *parent) 
{
	t_base	*node;(void)parent;

	if (!**lexer)
		return (0);
	node = mlc_base(SUB);
	while (**lexer != closing_par && **lexer)
	{
		if (**lexer == open_par)
			node->left = in_subshell(goto_next(lexer), node->left);
		else if (is_cmd(lexer))
			node->left = in_cmd(lexer, node->left);
		else if (**lexer == and)
			node->left = in_and(goto_next(lexer), node->left);
		else if (**lexer == or)
			node->left = in_or(goto_next(lexer), node->left);
		else if (**lexer == semicolon)
			node->left = in_scol(goto_next(lexer), node->left);
		else if (**lexer == pipe_delim)
			node->left = in_pipe(goto_next(lexer), node->left);
		else
			DEBUG("ERROR")
	}
	if (**lexer == closing_par)
	{
		goto_next(lexer);
		while (is_cmd(lexer))
		{
			DEBUG("SUBSHEL: %s", trad[**lexer])
			goto_next(lexer);
		}
	}
	else
		DEBUG("ERROR")
	return (node);
}

t_base	*in_pipe(t_lexer **lexer, t_base *left)
{
	t_base	*node;

	if (!**lexer)
		return (0);
	node = mlc_base(PPL);
	node->left = left;
	if (**lexer == open_par)
		node->right = in_subshell(goto_next(lexer), 0);
	else if (is_cmd(lexer))
		node->right = in_cmd(lexer, 0);
	else
		DEBUG("ERROR")
	return (node);
}

t_base	*in_and(t_lexer **lexer, t_base *left)
{
	t_base	*node;
	if (!**lexer)
		return (0);
	node = mlc_base(AND);
	node->left = left;
	if (**lexer == open_par)
		node->right = in_subshell(goto_next(lexer), 0);
	else if (is_cmd(lexer))
		node->right = in_cmd(lexer, 0);
	return (node);
}

t_base	*in_or(t_lexer **lexer, t_base *left)
{
	t_base	*node;

	if (!**lexer)
		return (0);
	node = mlc_base(OR);
	node->left = left;
	if (**lexer == open_par)
		node->right = in_subshell(goto_next(lexer), 0);
	else if (is_cmd(lexer))
		node->right = in_cmd(lexer, 0);
	return (node);
}

t_base	*in_scol(t_lexer **lexer, t_base *left)
{
	t_base	*node;

	node = mlc_base(SCOL);
	node->left = left;
	if (!**lexer || **lexer == closing_par)
		return (node);
	if (**lexer == open_par)		
		node->right = in_subshell(goto_next(lexer), 0);
	else if (is_cmd(lexer))
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
		else if (is_cmd(lexer))
			base = in_cmd(lexer, base);
		else if (**lexer == and)
			base = in_and(goto_next(lexer), base);
		else if (**lexer == or)
			base = in_or(goto_next(lexer), base);
		else if (**lexer == semicolon)
			base = in_scol(goto_next(lexer), base);
		else if (**lexer == pipe_delim)
			base = in_pipe(goto_next(lexer), base);
		else
			WAIT
	}
	return (base);
}

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

void	debug_lexer(t_lexer *lexer)
{

	
	printf("--LEXER: ");
	for (int i = 0; lexer[i]; ++i)
		printf("%s ", trad[lexer[i]]);
	printf("\n");
}

int main(void)
{
	t_lexer	*lexer;
	t_base *node;

	lexer = (t_lexer[]){open_par, word,and,word,closing_par,redir_in, word,semicolon, word, DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);

	lexer = (t_lexer[]){open_par,open_par,word,closing_par,and, word, closing_par,semicolon,open_par,word, semicolon,closing_par ,DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);

	lexer = (t_lexer[]){open_par, word,or, word, and, open_par,word, and, word,  closing_par,  closing_par, DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);

	lexer = (t_lexer[]){word, pipe_delim, word, pipe_delim, word, DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);
	
	lexer = (t_lexer[]){word, and, word, pipe_delim, word, DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);
	
	lexer = (t_lexer[]){open_par,open_par, word, semicolon, word,closing_par, pipe_delim, word, closing_par,DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);

	lexer = (t_lexer[]){open_par,open_par,  word, pipe_delim, word, closing_par, redir_in, word, pipe_delim, redir_out, word, redir_out, word, pipe_delim, word, closing_par,DONE};
	debug_lexer(lexer);
	node = make_base(&lexer);
	debug_tree(node);
}

