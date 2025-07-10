/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arco_get_next_line.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:15:31 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/10 17:35:36 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCO_GET_NEXT_LINE_H
# define ARCO_GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# if BUFFER_SIZE <= 0
#  error "BUFFER_SIZE must be strictly positive\n"
# endif

typedef struct s_dstr
{
	size_t	size ;
	char	*str;
}	t_dstr;

char	*get_next_null_arco(int fd);

int		foundnl(t_dstr out);
char	*clean_return(t_dstr *out, char *buff);

#endif
