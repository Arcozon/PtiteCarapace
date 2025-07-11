/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:18:16 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:26:35 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

# define SEP "| \t\v\n\r\f&<>;()"
# define OPENER "'\""

void		cmd_waitpid(t_cmd *cmd);
void		ms_exit(int rstatus, t_ms *ms);
uint64_t	ms_fork(int *pid, t_ms *ms);
uint64_t	cmd_open(int *oldfd, char *fname, int mode, char *pname);
uint64_t	pipe_ms(int pipes[2], t_ms *ms);
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

int			ft_strlen_without_q(char *str);
int			ft_strncmp_without_q(char *s_w_q, char *cmp, int len_w_q);
char		*ft_strnstr_without_q(const char *big, const char *l, size_t len);
char		*ft_substrjoin_with_slash(char *path, char *exe, size_t len);
int			ge_strncmp_weq(char *name, char *env_var, size_t n);
size_t		ft_varnamelen(const char var[]);

int			ge_isspace(char c);
int			is_end_ofesc_seq(char c);
char		*ge_strchr(char *str, char c);
uint32_t	findslash(const char *str);

void		free_table(t_hash_table *table);
void		free_ms(t_ms *ms);
void		free_node(t_base **pnode);
void		free_snip_lst(t_snippet *lst);
void		free_env(t_env *env);
void		free_snip_lst(t_snippet *lst);

char		*pass_whitespace(char *str);
char		*_basename(char *str);
void		print_until(char *str, char c, int fd);
bool		dollar_n_sep(char c);
bool		simple_sep(char c);
bool		dollar_sep_quote(char c);

#endif
