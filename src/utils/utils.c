/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:13:53 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 15:13:42 by gaeudes          ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1; 
		++s2;	
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

size_t	ft_varnamelen(const char var[])
{
	size_t	i;

	if (var[0] != '_' && !ft_isalpha(var[0]))
		return (0);
	i = 1;
	while (ft_isdigit(var[i]) || ft_isalpha(var[i]) || var[i] == '_')
		++i;
	return (i);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	close_fd(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

void	swap_fds(int *oldfd, int newfd)
{
	close_fd(oldfd);
	*oldfd = newfd;
}

char	*ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		++str;
	}
	if (c == 0)
		return (str);
	return (0);
}

char	*ft_substrjoin_with_slash(char *path, char *exe, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	j = ft_strlen(path);
	if (len > j)
		len = j;
	res = malloc((ft_strlen(exe) + len + 1 + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = path[i];
		++i;
	}
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

uint64_t	cmd_dup(t_cmd *cmd)
{
	if (cmd->fd_in >= 0 && dup2(cmd->fd_in, STDIN_FILENO) < 0)
		cmd->errors |= E_DUP;
	if (!cmd->errors && cmd->fd_out >= 0 && dup2(cmd->fd_out, STDIN_FILENO) < 0)
		cmd->errors |= E_DUP;
	close_fd(&cmd->fd_out);
	close_fd(&cmd->fd_in);
	return (cmd->errors);
}

uint64_t	ms_fork(int *pid, t_ms *ms)
{
	*pid = fork();
	if (*pid < 0)
		ms->errors |= E_FORK;
	return (ms->errors);
}

uint64_t	cmd_open(int *oldfd, char *fname, int mode, char *pname)
{
	int	new_fd;

	new_fd = open(fname, mode, 0644);
	if (new_fd < 0)
	{
		ms_perror(pname, fname);
		return (E_OPEN);
	}
	swap_fds(oldfd, new_fd);
	return (NO_ERR);
}
