/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_btree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:18:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 16:13:53 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BTREE_H
# define EXEC_BTREE_H

# include "types.h"

struct s_exec
{
	t_base		*base;

	int			pipes[2];
	int			next_fd_in;

	char		**env;

	uint64_t	errors;
};

#endif
