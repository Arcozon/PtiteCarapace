/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:31:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 15:39:33 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "types.h"

//	need to make a msstruct that countains pname, env...

int	bi_unset(int ac, char **av, t_env *env, int fds[2], char *pname);
int	bi_export(int ac, char **av, t_env *env, int fds[2], char *pname);
int	bi_env(int ac, char **av, t_env *env, int fds[2], char *pname);

#endif
