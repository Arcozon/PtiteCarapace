/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:09:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/19 10:52:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int main(int ac, char **av, char **env)
{
	t_snippet	limiters = {.next = 0, .token = here_doc};
	char	Blim[] = "EOF''";
	if (ac >= 2)
		limiters.ptr = av[1];
	else
		limiters.ptr = Blim;
	int fd = launch_heredocs(&limiters, env, 0, av[0]); 
	WAIT
	char c;
	while (read(fd, &c, 1) == 1)
		write(1, &c, 1);
}
