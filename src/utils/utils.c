/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:13:53 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 19:14:10 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

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

uint64_t	ms_fork(int *pid, t_ms *ms)
{
	*pid = fork();
	if (*pid < 0)
		ms->errors |= E_FORK;
	if (!*pid)
	{
		close_fd(&ms->history_fd);
		if (ms->msrc_fd >= 0)
			empty_gnl(ms->msrc_fd);
		close_fd(&ms->msrc_fd);
	}
	return (ms->errors);
}

int	is_end_ofesc_seq(char c)
{
	const char	end_secsq[] = "hlmnsuABCDEFGHKJ";
	int			i;

	i = 0;
	while (end_secsq[i])
	{
		if (end_secsq[i] == c)
			return (1);
		++i;
	}
	return (0);
}
