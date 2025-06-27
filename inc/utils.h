/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:18:16 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/27 14:07:56 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

void		cmd_waitpid(t_cmd *cmd);
void		ms_exit(int rstatus, t_ms *ms);
uint64_t	ms_fork(int *pid, t_ms *ms);
uint64_t	cmd_open(int *oldfd, char *fname, int mode, char *pname);
uint64_t	cmd_dup(t_cmd *cmd);
void		swap_fds(int *oldfd, int newfd);
void		close_fd(int *fd);

void		ge_bzero(void *vptr, size_t size);
void		*ge_calloc(size_t size);
void		*ge_memcpy(void *dst, const void *src, int64_t len);
uint64_t	ge_strlen(const char *str);
char		*ge_strdup(const char *str);
int			ge_strcmp(char *s1, char *s2);
int			get_ac(char **av);

char		*ft_substrjoin_with_slash(char *path, char *exe, size_t len);
int			ge_strncmp_weq(char *name, char *env_var, size_t n);
size_t		ft_varnamelen(const char var[]);

int			ge_isdigit(char c);
int			ge_isalpha(char c);
int			ge_isupper(char c);
char		*ge_strchr(char *str, char c);

void		free_ms(t_ms *ms);
void		free_node(t_base **pnode);

#endif
