/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:18:16 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/13 17:43:01 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

void		*ft_calloc(size_t size);
void		*ft_memcpy(void *dst, const void *src, int64_t len);
uint64_t	ft_strlen(const char *str);
char		*ft_strdup(const char *str);
inline void	ft_bzero(char *ptr, size_t size);
int			ft_strncmp_weq(char *name, char *env_var, size_t n);
int			ft_isdigit(char c);
int			ft_isalpha(char c);

#endif
