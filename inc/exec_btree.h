/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_btree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:18:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/15 11:49:59 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BTREE_H
# define EXEC_BTREE_H

# include "types.h"

struct s_exec
{
	t_base	*base;

	int		pipes[2];
	int		next_fd_in;

	char	**env;

	uint64_t	errors;
};



struct s_base
{
	enum
	{
		SCOL,
		AND,
		OR,
		PPL,
		CMD,
		SUB
	}	e_type;
	
	t_base	*left;
	t_base	*right;

	t_cmd	*cmd;

	int		fd_in;
	int		fd_out;

	uint8_t	subshell:1;
};

// 	Syntaxe:
//		semi[S](left, right);
// 		and[S](left, right);
// 		or[S](left, right);
// 		ppl[S](cmd, next);

// a --> ppl(a, 0)

// a | b --> pplS(a, pplS(b, 0))

// a && b	--> and(a, b)

// (a && b) --> andS(a, b)

// (a && b) | c && d --> and( pplS( andS(a, b), pplS(c, 0) ), d)

// a && b || c  -->  or( and(ppl(a, 0), ppl(b, 0)), ppl(c, 0) )

// (a) && b  -->  and(pplS(a, 0), b)

// a | (b ; c) --> pplS(a, )

#endif
