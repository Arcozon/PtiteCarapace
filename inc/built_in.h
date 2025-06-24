/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:31:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:52:38 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "types.h"

//	need to make a msstruct that countains ms, env...

int	bi_echo(int ac, char **av, int fds[2], t_ms *ms);
int	bi_cd(int ac, char **av, int fds[2], t_ms *ms);
int	bi_pwd(int ac, char **av, int fds[2], t_ms *ms);
int	bi_export(int ac, char **av, int fds[2], t_ms *ms);
int	bi_unset(int ac, char **av, int fds[2], t_ms *ms);
int	bi_env(int ac, char **av, int fds[2], t_ms *ms);
int	bi_alias(int ac, char **av, int fds[2], t_ms *ms);
int	bi_exit(int ac, char **av, int fds[2], t_ms *ms);

#endif
