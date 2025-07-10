/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:01:44 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/10 17:41:52 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arcoms.h"

void	trim_trailling_ws(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (!i)
		return ;
	while (i > 0)
	{
		if (!is_white_space(str[i - 1]) || str[i] == 10)
			break ;
		i--;
	}
	str[i] = 0;
}

static bool	fill_history(int fd, char **ptr_oldcmd)
{
	char	*str;
	char	*ptr;
	int		len;

	if (fd < 0)
		return (false);
	str = get_next_null_arco(fd);
	while (str)
	{
		ptr = pass_whitespace(str);
		len = ft_strlen(ptr);
		if (len >= 1 && ptr[len - 1] == '\n')
			ptr[len - 1] = 0;
		trim_trailling_ws(ptr);
		if (*ptr && ft_strcmp(ptr, *ptr_oldcmd))
		{
			add_history(ptr);
			free(*ptr_oldcmd);
			*ptr_oldcmd = ft_strdup(ptr);
		}
		free(str);
		str = get_next_null_arco(fd);
	}
	return (true);
}

int	ms_get_history_fd(char **ptr_oldcmd)
{
	static int	fd;

	if (!fd)
	{
		fd = open(MS_HISTORY, O_RDWR | O_CREAT | O_APPEND, 00666);
		if (fd < 0)
			return (-1);
		fill_history(fd, ptr_oldcmd);
	}
	return (fd);
}

void	ms_add_history(char *str, int fd, char **ptr_oldcmd)
{
	char	*ptr;

	ptr = pass_whitespace(str);
	trim_trailling_ws(ptr);
	if (!*ptr)
		return ;
	if (ft_strcmp(ptr, *ptr_oldcmd))
	{
		add_history(ptr);
		free(*ptr_oldcmd);
		*ptr_oldcmd = ft_strdup(ptr);
		if (fd < 0)
			return ;
		ft_putstr_fd(ptr, fd);
		ft_putchar_fd(0, fd);
	}
}
