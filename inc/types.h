/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:21:12 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 16:16:17 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <wait.h>

typedef struct s_heredoc	t_hdoc;
typedef struct s_exe_hdoc	t_exe_hdoc;
typedef struct s_redir		t_redir;

typedef struct s_cmd		t_cmd;
typedef struct s_ppl		t_ppl;
typedef struct s_base		t_base;

typedef struct s_exec		t_exec;

typedef struct s_env		t_env;

enum						e_token;
typedef struct s_node		t_snippet;

#endif
