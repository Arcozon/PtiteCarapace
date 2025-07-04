/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arco_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:19:39 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/04 12:53:39 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	found_null(t_dstr out)
{
	size_t	i;

	i = 0;
	if (!out.str)
		return (0);
	while (i < out.size)
	{
		if (out.str[i] == '\0')
			return (1);
		++i;
	}
	return (0);
}

char	*clean_return(t_dstr *out, char *buff)
{
	free(buff);
	free(out->str);
	out->str = 0;
	out->size = 0;
	return (0);
}

// 0 on success
int	cat_buff_out(t_dstr *out, char buff[BUFFER_SIZE], int br)
{
	char	*new;
	size_t	i;

	if (!br)
		return (0);
	new = malloc(sizeof(char) * (out->size + br));
	if (!new)
		return (1);
	i = 0;
	while (i < out->size)
	{
		new[i] = out->str[i];
		++i;
	}
	i = 0;
	while (i < (size_t)br)
	{
		new[out->size + i] = buff[i];
		++i;
	}
	free(out->str);
	out->size += br;
	out->str = new;
	return (0);
}

// 0 on success
int	cut_str(t_dstr *out, size_t ret_len, int f_donereading)
{
	char	*str;
	size_t	i;

	if (f_donereading)
		return (clean_return(out, 0), 0);
	str = malloc(sizeof(char) * (out->size - ret_len));
	if (!str)
		return (1);
	i = 0;
	while (i < out->size - ret_len)
	{
		str[i] = out->str[ret_len + i];
		++i;
	}
	free(out->str);
	out->size = i;
	out->str = str;
	return (0);
}

// write(1, ret, i); to print binary files
char	*create_ret(t_dstr *out)
{
	char	*ret;
	size_t	ret_len;
	size_t	i;

	ret_len = 0;
	while (ret_len < out->size && out->str[ret_len] != '\0')
		++ret_len;
	ret_len += ret_len < out->size;
	ret = malloc(sizeof(char) * (ret_len + 1));
	if (!ret)
		return (clean_return(out, 0));
	i = 0;
	while (i < ret_len)
	{
		ret[i] = out->str[i];
		++i;
	}
	ret[i] = 0;
	if (cut_str(out, ret_len, ret_len == out->size))
	{
		free(ret);
		clean_return(out, 0);
		return (0);
	}
	return (ret);
}

char	*get_next_null_arco(int fd)
{
	static t_dstr	out = {0};
	char			*buff;
	int				br;

	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff)
		return (clean_return(&out, buff));
	br = BUFFER_SIZE;
	while (1)
	{
		if (!br && !out.str)
			return (clean_return(&out, buff));
		if (found_null(out) || br == 0)
			return (free(buff), create_ret(&out));
		br = read(fd, buff, BUFFER_SIZE);
		if (br < 0)
			return (clean_return(&out, buff));
		if (cat_buff_out(&out, buff, br))
			return (clean_return(&out, buff));
	}
}

// #include "get_next_line.h"
// #include <stdio.h>
// #include <fcntl.h>

// int    main(void)
// {
//     int        fd;
//     char    *line;

//     fd = open("giant_line.txt", O_RDONLY);
//     // fd = 0;
//     if (fd < 0)
//     {
//         perror("open");
//         return (1);
//     }
//     line = get_next_line(fd);
//     // while (line != NULL)
//     // {
//         printf("%s", line);
//         // free(line);
//     //     line = get_next_line(fd);
//     // }
//     close(fd);
//     return (0);
// }
