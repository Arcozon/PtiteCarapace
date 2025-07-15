/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:24:52 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_clear(int ac, char **av, int fds[2], t_ms *ms)
{
	write(fds[PIPE_WRITE], "\033[H\033[2J\033[3J", 11);
	return (0);
	(void)ac, (void)av, (void)ms;
}
