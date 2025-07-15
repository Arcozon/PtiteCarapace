/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ge_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:26:10 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ge_bzero(void *vptr, size_t size)
{
	char	*ptr;

	ptr = vptr;
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

void	*ge_calloc(size_t size)
{
	char	*res;

	res = malloc(size);
	if (!res)
		return (res);
	inline_bzero(res, size);
	return (res);
}

void	*ge_memcpy(void *dst, const void *src, int64_t len)
{
	while (len--)
		((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	return (dst);
}
