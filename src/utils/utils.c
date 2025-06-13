/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:13:53 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/13 17:42:28 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

inline void	ft_bzero(char *ptr, size_t size)
{
	while ((size_t)ptr & 0b111 && size)
	{
		*ptr = 0;
		++ptr;
		--size;
	}
	while (size & ~0b111)
	{
		*(size_t *)ptr = 0;
		ptr += 8;
		size -= 8;
	}
	while (size)
	{
		*ptr = 0;
		++ptr;
		--size;
	}
}

static inline void	__attribute__((always_inline))
	inline_bzero(char *ptr, size_t size)
{
	while ((size_t)ptr & 0b111 && size)
	{
		*ptr = 0;
		++ptr;
		--size;
	}
	while (size & ~0b111)
	{
		*(size_t *)ptr = 0;
		ptr += 8;
		size -= 8;
	}
	while (size)
	{
		*ptr = 0;
		++ptr;
		--size;
	}
}
void	*ft_calloc(size_t size)
{
	char	*res;

	res = malloc(size);
	if (!res)
		return (res);
	inline_bzero(res, size);
	return (res);
}

uint64_t	ft_strlen(const char *str)
{
	uint64_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, int64_t len)
{
	while (len--)
		((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	return (dst);
}

char	*ft_strdup(const char *str)
{
	uint64_t	len;
	char		*res;

	len = ft_strlen(str) + 1;
	res = malloc(len);
	if (res)
		ft_memcpy(res, str, len);
	return (res);
}

int	ft_strncmp_weq(char *name, char *env_var, size_t n)
{
	while (n && *name)
	{
		if (*name != *env_var)
			return (1);
		--n;
		++name;
		++env_var;
	}
	if (!n && *env_var == '=')
		return (0);
	return (1);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
