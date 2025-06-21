/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:21:12 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 15:03:35 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <wait.h>

typedef struct s_ms			t_ms;

typedef struct s_exe_hdoc	t_x_hdoc;

typedef struct s_cmd		t_cmd;
typedef struct s_base		t_base;

typedef struct s_env		t_env;

enum						e_token;
typedef struct s_node		t_snippet;

typedef int					(*t_builin_fct)(int, char **, int[2], t_ms *);

#endif
