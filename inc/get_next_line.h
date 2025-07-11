/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:19:30 by amouflet          #+#    #+#             */
/*   Updated: 2025/07/11 19:45:11 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define __BUFFER_SIZE__ 512

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE __BUFFER_SIZE__
# endif /*BUFFER_SIZE*/

# if (BUFFER_SIZE <= 0)
#  undef BUFFER_SIZE
#  define BUFFER_SIZE __BUFFER_SIZE__
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_stash
{
	char			*str;
	struct s_stash	*next;
}	t_buf;

char	*get_next_line(int fd);
bool	is_line_terminated(char *line, int i);
int		new_elem_back(t_buf **begin, char *buf);
int		free_lst(t_buf **lst);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	empty_gnl(int fd);
int		read_null_terminated(int fd, char *buffer, int buffer_size);
int		in_str_len(char *str, char c, int len);

typedef struct s_dstr
{
	size_t	size ;
	char	*str;
}	t_dstr;

char	*get_next_null_arco(int fd);

int		found_null(t_dstr out);
char	*clean_return(t_dstr *out, char *buff);

#endif /*GET_NEXT_LINE_H*/
