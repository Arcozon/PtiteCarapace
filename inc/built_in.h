/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:31:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:13:50 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "types.h"

# define TABLE_SIZE 512 // Always 2^n to keep the speed
# define PRIME_HASH 53
# define FORBIDDEN_CHAR_ALIAS " \t\n\v\r\f/!@#$*&():"

struct s_pair
{
	int		len;
	char	*key;
	char	*value;
	t_pair	*next;
};

struct s_hash_table
{
	t_pair	*bucket[TABLE_SIZE];
};

void		set_pair(t_hash_table *table, t_pair *pair);
t_pair		*create_pair(char *str);
void		remove_pair(t_hash_table *table, t_pair *pair);

int	bi_echo(int ac, char **av, int fds[2], t_ms *ms);
int	bi_clear(int ac, char **av, int fds[2], t_ms *ms);
int	bi_cd(int ac, char **av, int fds[2], t_ms *ms);
int	bi_pwd(int ac, char **av, int fds[2], t_ms *ms);
int	bi_export(int ac, char **av, int fds[2], t_ms *ms);
int	bi_unset(int ac, char **av, int fds[2], t_ms *ms);
int	bi_env(int ac, char **av, int fds[2], t_ms *ms);
int	bi_alias(int ac, char **av, int fds[2], t_ms *ms);
int	bi_exit(int ac, char **av, int fds[2], t_ms *ms);
int	bi_status(int ac, char **av, int fds[2], t_ms *ms);

#endif
