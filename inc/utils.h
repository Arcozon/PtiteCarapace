/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:18:16 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/18 13:55:04 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

void	close_fd(int *fd);

inline void		ft_bzero(char *ptr, size_t size);
void		*ft_calloc(size_t size);
void		*ft_memcpy(void *dst, const void *src, int64_t len);
uint64_t	ft_strlen(const char *str);
char		*ft_strdup(const char *str);
int			ft_strcmp(char *s1, char *s2);

int			ft_strncmp_weq(char *name, char *env_var, size_t n);
size_t		ft_varnamelen(const char var[]);

int			ft_isdigit(char c);
int			ft_isalpha(char c);

#endif
