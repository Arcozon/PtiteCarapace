/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ge_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:22:57 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 18:10:38 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

char	*ge_strdup(const char *str)
{
	uint64_t	len;
	char		*res;

	len = ge_strlen(str) + 1;
	res = malloc(len);
	if (res)
		ge_memcpy(res, str, len);
	return (res);
}

uint64_t	ge_strlen(const char *str)
{
	uint64_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

int	ge_strncmp_weq(char *name, char *env_var, size_t n)
{
	while (n && *name)
	{
		if (*name != *env_var || *env_var == '=')
			return (1);
		--n;
		++name;
		++env_var;
	}
	if (!n && *env_var == '=')
		return (0);
	return (1);
}

int	ge_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_substrjoin_with_slash(char *path, char *exe, size_t len)
{
	const uint32_t	insert_slash = (len != 0);
	char			*res;
	size_t			i;
	size_t			j;

	j = ge_strlen(path);
	if (len > j)
		len = j;
	res = malloc((ge_strlen(exe) + len + insert_slash + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = path[i];
		++i;
	}
	if (insert_slash)
		res[i++] = '/';
	j = 0;
	while (exe[j])
	{
		res[i + j] = exe[j];
		++j;
	}
	res[i + j] = '\0';
	return (res);
}
