/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:21:12 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/13 15:03:08 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <wait.h>

typedef struct s_heredoc	t_hdoc;
typedef struct s_exe_hdoc	t_exe_hdoc;
typedef	struct s_redir		t_redir;

typedef struct s_cmd		t_cmd;

typedef struct s_ppline		t_ppline;
typedef struct s_opp_node	t_opp_node;

typedef struct s_exec		t_exec;

typedef struct s_env		t_env;

#endif
